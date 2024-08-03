#include <stdint.h>

#include "system_fr30xx.h"

/*-------------------------------------------------------------------------
    Function    :  ascii_char2val             ----add by chsheng, chsheng@accelsemi.com
    Return: -1=error
    Description:
        'a' -> 0xa  'A' -> 0xa
-------------------------------------------------------------------------*/
static char ascii_char2val(const char c)
{
    if(c>='0' && c<='9')
        return c-'0';
    if((c>='a' && c<='f') || (c>='A' && c<='F'))
        return (c&0x7)+9;

    return (char)(-1);
}

/*-------------------------------------------------------------------------
    Function    :  ascii_strn2val             ----add by chsheng, chsheng@accelsemi.com
    Return: -1=error
    Description:
        str = "123" bas = 10 return 123
        str = "123" bas = 16 return 0x123        
-------------------------------------------------------------------------*/
int ascii_strn2val( const char str[], char base, char n)
{
    int val = 0;
    char v;
    while(n != 0){

        v = ascii_char2val(*str);
#if 0
        if (v == -1 || v >= base) 
            return -1;
#else
        if (v == (char)(-1) || v >= base)
        {
            if(val == 0) //to filter abormal beginning and ending
            {
                str ++;
                n --;
                continue;
            }
            else
            {
                break;
            }
        }
#endif

        val = val*base + v;
        
        str++;
        n--;
    }
    return val;
}

#ifdef __CC_ARM
__RAM_CODE static __asm void cpu_delay(uint32_t ulCount)
{
    PRESERVE8
start
    subs    r0, #1
    bne     start
    bx      lr
}
#endif  // __CC_ARM

#if defined(__GNUC__)
__RAM_CODE static void cpu_delay(uint32_t ulCount)
{
    __asm volatile(
                " 1: subs   %0, #1  \n"
                " bne       1b      \n"
                :
                :"r"(ulCount)
                :
                );
}
#endif  // __GNUC__

#if defined(__ICCARM__)
__RAM_CODE static void cpu_delay(uint32_t ulCount)
{
    __asm volatile(
                "loop: subs   %0, #1  \n"
                "bne       loop      \n"
                :
                :"r"(ulCount)
                :
                );
}
#endif  // __ICCARM__

__RAM_CODE void co_delay_100us(uint32_t num)
{
    volatile uint32_t threshold;
    volatile uint8_t pclk_cfg;

    if(num == 0) {
        return;
    }

    pclk_cfg = system_get_CoreClock() / 1000000;

    threshold = 400 * num;
    if(pclk_cfg == 24) {
        threshold <<= 1;
    }
    else if(pclk_cfg == 48) {
        threshold <<= 2;
    }
    else if(pclk_cfg == 96) {
        threshold <<= 3;
    }
    else {
        threshold *= (pclk_cfg / 12);
    }

    cpu_delay(threshold);
}

__RAM_CODE void co_delay_10us(uint32_t num)
{
    volatile uint32_t threshold;
    volatile uint8_t pclk_cfg;

    if(num == 0) {
        return;
    }

    pclk_cfg = system_get_CoreClock() / 1000000;

    threshold = 40 * num;
    if(pclk_cfg == 24) {
        threshold <<= 1;
    }
    else if(pclk_cfg == 48) {
        threshold <<= 2;
    }
    else if(pclk_cfg == 96) {
        threshold <<= 3;
    }
    else {
        threshold *= (pclk_cfg / 12);
    }

    cpu_delay(threshold);
}

#ifdef __CC_ARM
__RAM_CODE __asm void mul_64(uint32_t *low, uint32_t *high, uint32_t mul1, uint32_t mul2)
{
    PRESERVE8

    push {r4, r5, lr}

    umull r4, r5, r2, r3
    str r4, [r0]
    str r5, [r1]

    pop {r4, r5, pc}
}
#endif // __CC_ARM
#if defined(__ARMCC_VERSION) || defined(__GNUC__) || defined(__ICCARM__)
__RAM_CODE void mul_64(uint32_t *low, uint32_t *high, uint32_t mul1, uint32_t mul2)
{
    __asm volatile(
                " umull r4, r5, %2, %3  \n"
                " str r4, [%0]          \n"
                " str r5, [%1]          \n"
                :
                : "r"(low), "r"(high), "r"(mul1), "r"(mul2)
                : "r4", "r5"
                );
}
#endif // defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)

/*
 * result = (high * (0xFFFFFFFF+1) + low) / div
 *          0xFFFFFFFF = a * div + b
 *          low = c * div + d
 *          sub = (high * (1 + b) + d) / div
 * result = a * high + c + sub
 *
 * limitation: high * (1 + b) + d should be no larger than 0xffffffff
 */
__RAM_CODE uint32_t simple_div_64(uint32_t low, uint32_t high, uint32_t div)
{
    uint32_t a, b, c, d, sub;

    c = low / div;
    
    if(high == 0) {
        return c;
    }

    a = 0xFFFFFFFF / div;
    b = 0xFFFFFFFF % div;
    d = low % div;
    sub = (high * (1 + b) + d) / div;

    return (a * high + c + sub);
}
