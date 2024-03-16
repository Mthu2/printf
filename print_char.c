#include "main.h"

/**
 * printf_character - prints a charactor
 * variadic: arguments
 * return: 1
 */
int printf_character(va_list variadic)
{
	char str;
	
	str - va_arg(variadic, int);
	_putchar(str);

	return (1);
}
