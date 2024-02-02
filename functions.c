#include "main.h"

/**
 * print_char - Prints a char
 * @types:argument list
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: Width
 * @accuracy: accuray indicator
 * @size: Size indicator
 * Return: Sum of chars
 */
int print_char(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, cushion, flags, width, accuracy, size));
}
/**
 * print_string - Prints a string
 * @types:argument list
 * @cushion: handles print [array]
 * @flags:  Calculates active flags
 * @width: get width.
 * @accuracy: accuray indicator
 * @size: Size indicator
 * Return: Sum of chars
 */
int print_string(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(cushion);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(accuracy);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (accuracy >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (accuracy >= 0 && accuracy < length)
		length = accuracy;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/**
 * print_percent - Prints a percent sign
 * @types: Lista of arguments
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: get width.
 * @accuracy: accuray indicator
 * @size: Size indicator
 * Return: Sum of chars
 */
int print_percent(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{
	UNUSED(types);
	UNUSED(cushion);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(accuracy);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - Print int
 * @types: Lista of arguments
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: get width.
 * @accuracy: accuray indicator
 * @size: Size indicator
 * Return: Sum of chars
 */
int print_int(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		cushion[i--] = '0';

	cushion[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		cushion[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, cushion, flags, width, accuracy, size));
}


/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: obtain width.
 * @accuracy: accuray indicator
 * @size: Size indicator
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char cushion[],
	int flags, int width, int accuracy, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(cushion);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(accuracy);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
