#include "main.h"

/**
 * print_unsigned - Prints an unsigned number
 * @types:argument list
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: get width
 * @accuracy: accuray indicator
 * @size: Size indicator
 * Return: Sum of chars.
 */
int print_unsigned(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		cushion[i--] = '0';

	cushion[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		cushion[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, cushion, flags, width, accuracy, size));
}
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: Lista of arguments
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: get width
 * @accuracy: accuray indicator
 * @size: Size indicator
 * Return: Sum of chars
 */
int print_octal(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		cushion[i--] = '0';

	cushion[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		cushion[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		cushion[i--] = '0';

	i++;

	return (write_unsgnd(0, i, cushion, flags, width, accuracy, size));
}
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: get width
 * @accuracy: accuray indicator
 * @size: Size indicator
 * Return: Sum of chars
 */
int print_hexadecimal(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{
	return (print_hexa(types, "0123456789abcdef", cushion,
		flags, 'x', width, accuracy, size));
}
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Lista of arguments
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: get width
 * @accuracy: accuray indicator
 * @size: Size indicator
 * Return: Sum of chars
 */
int print_hexa_upper(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", cushion,
		flags, 'X', width, accuracy, size));
}
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: Lista of arguments
 * @find_to: Array of values to map the number to
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @accuracy: Accuray indicator
 * @size: Size indicator
 * @size: Size specification
 * Return: Sum of chars
 */
int print_hexa(va_list types, char find_to[], char cushion[],
	int flags, char flag_ch, int width, int accuracy, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		cushion[i--] = '0';

	cushion[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		cushion[i--] = find_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		cushion[i--] = flag_ch;
		cushion[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, cushion, flags, width, accuracy, size));
}
