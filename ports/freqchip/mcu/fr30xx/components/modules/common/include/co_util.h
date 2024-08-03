#ifndef _CO_UTIL_H
#define _CO_UTIL_H

#include <stdint.h>

int ascii_strn2val( const char str[], char base, char n);

void co_delay_100us(uint32_t count);
void co_delay_10us(uint32_t count);

void mul_64(uint32_t *low, uint32_t *high, uint32_t mul1, uint32_t mul2);
uint32_t simple_div_64(uint32_t low, uint32_t high, uint32_t div);

#endif //_CO_UTIL_H
