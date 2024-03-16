#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int _putchar(char c);
int _printf(const char *format, ...);
int printf_character(va_list variadic);
int printf_str(va_list variadic);
int _strlen(char *str);
int _strlenc(const char *str);
int print_percent(void);
int print_i(va_list args);
int print_d(va_list args);
int print_binary(va_list val);
int print_unsgnd(va_list args);
int print_octal(va_list val);
int print_hexa(va_list val);
int _printf(const char *format, ...);

#endif
