#include "main.h"

/**
 * _putchar - writes character c to stdout.
 * @c: the printed character
 * Return: 1 (success) -1 (error)
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
