#include "main.h"

/**
 * printf_str - print string.
 * variadic: argument.
 * Return: string length
 */

int printf_str(va_list variadic)
{
	char *str;
	int i;
	int length;

	str = va_arg(variadic, char *);
	if (str == NULL)
	{
		str = "(null";
		length = _strlen(str);
		for (i = 0; i < length; i++)
			_putchar(str[i]);
		return (length);
	}
	else
	{
		length = _strlen(str);
		for (i =0; i < length; i++)
			_putchar(str[i]);
		return (length);
	}
}
