#ifndef _CO_PRINTF_H
#define _CO_PRINTF_H

#include <stdio.h>
#include <stdarg.h>

int fputc_uart0(int ch, FILE *f);
int fputc_uart1(int ch, FILE *f);
int _write_uart0(int fd, char *pBuffer, int size);
int _write_uart1(int fd, char *pBuffer, int size);

int print(char **out, const char *format, va_list args);
int co_printf(const char *format, ...);
int co_sprintf(char *out, const char *format, ...);

extern int (*fputc_imp)(int ch, FILE *f);
extern int (*_write_imp)(int fd, char *pBuffer, int size);

#endif

