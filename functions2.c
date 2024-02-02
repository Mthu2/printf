#include "main.h"

/**
 * print_poinetr – outputs value of a p_r variable
 * @types:argument list
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: get output
 * @accuracy: accuracy output
 * @size: Size output
 * Return: amount of chars to print.
 */
int print_pointer(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char find_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	cushion[BUFF_SIZE - 1] = '\0';
	UNUSED(accuracy);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		cushion[ind--] = find_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	return (write_p_r(cushion, ind, length,
		width, flags, padd, extra_c, padd_start));
}
/**
 * print_n_p - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: get width
 * @accuracy: Accuray indicator
 * @size: Size indicator
 * Return: Sum of chars
 */
int print_n_p(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(accuracy);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			cushion[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], cushion, i + offset);

		i++;
	}

	cushion[i + offset] = '\0';

	return (write(1, cushion, i + offset));
}
/**
 * print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: get width
 * @accuracy: Accuray indicator
 * @size: Size indicator
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(cushion);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(accuracy);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/**
 * print_rot13string - Print a string in rot13.
 * @types: Lista of arguments
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: get width
 * @accuracy: Accuray indicator
 * @size: Size indicator
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(cushion);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(accuracy);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
