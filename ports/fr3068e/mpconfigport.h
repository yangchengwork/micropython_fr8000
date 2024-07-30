#include <stdint.h>

// Use the minimal starting configuration (disables all optional features).
#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_MINIMUM)

// You can disable the built-in MicroPython compiler by setting the following
// config option to 0.  If you do this then you won't get a REPL prompt, but you
// will still be able to execute pre-compiled scripts, compiled with mpy-cross.
#define MICROPY_ENABLE_COMPILER     (1)

// #define MICROPY_QSTR_EXTRA_POOL           mp_qstr_frozen_const_pool

// Python internal features.
#define MICROPY_ENABLE_GC                       (1)
#define MICROPY_HELPER_REPL                     (1)
#define MICROPY_ERROR_REPORTING                 (MICROPY_ERROR_REPORTING_TERSE)
#define MICROPY_FLOAT_IMPL                      (MICROPY_FLOAT_IMPL_FLOAT)

// Fine control over Python builtins, classes, modules, etc.
#define MICROPY_PY_ASYNC_AWAIT                  (1)
#define MICROPY_PY_BUILTINS_SET                 (1)
#define MICROPY_PY_ATTRTUPLE                    (1)
#define MICROPY_PY_COLLECTIONS                  (1)
#define MICROPY_PY_MATH                         (1)
#define MICROPY_PY_IO                           (0)
#define MICROPY_PY_STRUCT                       (1)
#define MICROPY_PY_ARRAY                        (1)
#define MICROPY_PY_SYS                          (1)
#define MICROPY_PY_ASYNCIO                      (0)
#define MICROPY_PY_JSON                         (0)
#define MICROPY_PY_BINASCII                     (0)
#define MICROPY_PY_TIME                         (0)
#define MICROPY_PY_RANDOM                       (0)

// Type definitions for the specific machine.

typedef intptr_t mp_int_t; // must be pointer size
typedef uintptr_t mp_uint_t; // must be pointer size
typedef long mp_off_t;

// We need to provide a declaration/definition of alloca().
#include <alloca.h>

// Define the port's name and hardware.
#define MICROPY_HW_BOARD_NAME "FR3068E-C EVB1.0"
#define MICROPY_HW_MCU_NAME   "fr30xx"

#define MP_STATE_PORT MP_STATE_VM

#define MICROPY_PY_BUILTINS_HELP                (1)
#define MICROPY_PY_BUILTINS_HELP_TEXT           gumpyang_help_text
#define MICROPY_PY_BUILTINS_HELP_MODULES        (1)
