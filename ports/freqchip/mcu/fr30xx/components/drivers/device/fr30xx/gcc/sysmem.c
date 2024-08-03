#if 1
/* Includes */
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>

#include "fr30xx.h"

/* Variables */
extern int errno;
static uint32_t malloc_cpu_sr;
static uint32_t counter = 0;

/* Functions */

/**
 _sbrk
 Increase program data space. Malloc and related functions depend on this
**/
caddr_t _sbrk(int incr)
{
    extern char _heap_start asm("_heap_start");
    extern char _heap_end asm("_heap_end");
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
        heap_end = &_heap_start;

    prev_heap_end = heap_end;
    if (heap_end + incr > &_heap_end)
    {
        errno = ENOMEM;
        return (caddr_t) -1;
    }

    heap_end += incr;

    return (caddr_t) prev_heap_end;
}

void __malloc_lock(struct _reent *r)
{
    uint32_t tmp_sr;
    (void)(r);

    tmp_sr = GLOBAL_INT_DISABLE_V2();
    if (counter == 0) {
        malloc_cpu_sr = tmp_sr;
    }
    counter++;
}

void __malloc_unlock(struct _reent *r)
{
    (void)(r);
    
    counter--;

    if (counter == 0) {
        GLOBAL_INT_RESTORE_V2(malloc_cpu_sr);
    }
}

#else
#include <stdlib.h> // maps to newlib...
#include <malloc.h> // mallinfo...
#include <errno.h>  // ENOMEM
#include <stdbool.h>
#include <stddef.h>

#include "newlib.h"
#if ((__NEWLIB__ == 2) && (__NEWLIB_MINOR__ < 5)) || ((__NEWLIB__ == 4) && (__NEWLIB_MINOR__ > 2) || (__NEWLIB__ < 2) || (__NEWLIB__ > 4))
  #warning "This wrapper was verified for newlib versions 2.5 - 4.2; please ensure newlib's external requirements for malloc-family are unchanged!"
#endif

#include "FreeRTOS.h" // defines public interface we're implementing here
#if !defined(configUSE_NEWLIB_REENTRANT) ||  (configUSE_NEWLIB_REENTRANT!=1)
  #warning "#define configUSE_NEWLIB_REENTRANT 1 // Required for thread-safety of newlib sprintf, dtoa, strtok, etc..."
  // If you're *REALLY* sure you don't need FreeRTOS's newlib reentrancy support, comment out the above warning...
#endif
#include "task.h"

#define MALLOCS_INSIDE_ISRs
#define NDEBUG

// ================================================================================================
// External routines required by newlib's malloc (sbrk/_sbrk, __malloc_lock/unlock)
// ================================================================================================

#ifdef MALLOCS_INSIDE_ISRs
    #define DRN_ENTER_CRITICAL_SECTION(_usis) { _usis = taskENTER_CRITICAL_FROM_ISR(); } // Disables interrupts (after saving prior state)
    #define DRN_EXIT_CRITICAL_SECTION(_usis)  { taskEXIT_CRITICAL_FROM_ISR(_usis);     } // Re-enables interrupts (unless already disabled prior taskENTER_CRITICAL)
#else
    #define DRN_ENTER_CRITICAL_SECTION(_usis) vTaskSuspendAll(); // Note: safe to use before FreeRTOS scheduler started, but not in ISR
    #define DRN_EXIT_CRITICAL_SECTION(_usis)  xTaskResumeAll();  // Note: safe to use before FreeRTOS scheduler started, but not in ISR
#endif

#ifdef MALLOCS_INSIDE_ISRs // block interrupts during free-storage use
    static UBaseType_t malLock_uxSavedInterruptStatus;
#endif
#ifndef NDEBUG
    static int totalBytesProvidedBySBRK = 0;
#endif
static int heapBytesRemaining;
extern char _heap_start, _heap_end;  // symbols from linker LD command file

// Use of vTaskSuspendAll() in _sbrk_r() is normally redundant, as newlib malloc family routines call
// __malloc_lock before calling _sbrk_r(). Note vTaskSuspendAll/xTaskResumeAll support nesting.

//! _sbrk_r version supporting reentrant newlib (depends upon above symbols defined by linker control file).
void * _sbrk_r(struct _reent *pReent, int incr)
{
#ifdef MALLOCS_INSIDE_ISRs // block interrupts during free-storage use
    UBaseType_t usis; // saved interrupt status
#endif
    static char *currentHeapEnd = &_heap_start;

    if(heapBytesRemaining==0) {
        heapBytesRemaining = (int)((&_heap_end)-(&_heap_start));
    }

    DRN_ENTER_CRITICAL_SECTION(usis);
    if (currentHeapEnd + incr > &_heap_end) {
        // Ooops, no more memory available...
        #if( configUSE_MALLOC_FAILED_HOOK == 1 )
          {
            extern void vApplicationMallocFailedHook( void );
            DRN_EXIT_CRITICAL_SECTION(usis);
            vApplicationMallocFailedHook();
          }
        #elif defined(configHARD_STOP_ON_MALLOC_FAILURE)
            // If you want to alert debugger or halt...
            // WARNING: brkpt instruction may prevent watchdog operation...
            while(1) { __asm("bkpt #0"); } // Stop in GUI as if at a breakpoint (if debugging, otherwise loop forever)
        #else
            // Default, if you prefer to believe your application will gracefully trap out-of-memory...
            pReent->_errno = ENOMEM; // newlib's thread-specific errno
            DRN_EXIT_CRITICAL_SECTION(usis);
        #endif
        return (char *)-1; // the malloc-family routine that called sbrk will return 0
    }
    // 'incr' of memory is available: update accounting and return it.
    char *previousHeapEnd = currentHeapEnd;
    currentHeapEnd += incr;
    heapBytesRemaining -= incr;
#ifndef NDEBUG
    totalBytesProvidedBySBRK += incr;
#endif
    DRN_EXIT_CRITICAL_SECTION(usis);
    return (char *) previousHeapEnd;
}

//! non-reentrant sbrk uses is actually reentrant by using current context
// ... because the current _reent structure is pointed to by global _impure_ptr
char * sbrk(int incr)
{
    return _sbrk_r(_impure_ptr, incr);
}

//! _sbrk is a synonym for sbrk.
char * _sbrk(int incr)
{
    return sbrk(incr);
}

void __malloc_lock(struct _reent *r)
{
    (void)(r);
#if defined(MALLOCS_INSIDE_ISRs)
    DRN_ENTER_CRITICAL_SECTION(malLock_uxSavedInterruptStatus);
#else
    bool insideAnISR = xPortIsInsideInterrupt();
    configASSERT( !insideAnISR ); // Make damn sure no more mallocs inside ISRs!!
    vTaskSuspendAll();
#endif
}

void __malloc_unlock(struct _reent *r)
{
    (void)(r);
#if defined(MALLOCS_INSIDE_ISRs)
    DRN_EXIT_CRITICAL_SECTION(malLock_uxSavedInterruptStatus);
#else
    (void)xTaskResumeAll();
#endif
}

size_t heap_available_size( void )
{
    struct mallinfo mi = mallinfo(); // available space now managed by newlib
    return mi.fordblks + heapBytesRemaining; // plus space not yet handed to newlib by sbrk
}

// newlib also requires implementing locks for the application's environment memory space,
// accessed by newlib's setenv() and getenv() functions.
// As these are trivial functions, momentarily suspend task switching (rather than semaphore).
// Not required (and trimmed by linker) in applications not using environment variables.
// ToDo: Move __env_lock/unlock to a separate newlib helper file.
void __env_lock()
{
    vTaskSuspendAll();
}

void __env_unlock()
{
    (void)xTaskResumeAll();
}

#if 0 // Provide malloc debug and accounting wrappers
/// /brief  Wrap malloc/malloc_r to help debug who requests memory and why.
/// To use these, add linker options: -Xlinker --wrap=malloc -Xlinker --wrap=_malloc_r
// Note: These functions are normally unused and stripped by linker.
size_t TotalMallocdBytes;
int MallocCallCnt;
static bool inside_malloc;

void *__wrap_malloc(size_t nbytes)
{
    extern void * __real_malloc(size_t nbytes);
    MallocCallCnt++;
    TotalMallocdBytes += nbytes;
    inside_malloc = true;
    void *p = __real_malloc(nbytes); // will call malloc_r...
    inside_malloc = false;
    return p;
}

void *__wrap__malloc_r(void *reent, size_t nbytes)
{
    (void)(reent);
    extern void * __real__malloc_r(size_t nbytes);
    if(!inside_malloc) {
        MallocCallCnt++;
        TotalMallocdBytes += nbytes;
    }
    void *p = __real__malloc_r(nbytes);
    return p;
}
#endif
#endif
