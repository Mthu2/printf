#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags.
 * @width: get width.
 * @accuracy: accuracy specifier
 * @size: Size indicator
 *
 * Return: Sum of chars.
 */
int handle_write_char(char c, char cushion[],
	int flags, int width, int accuracy, int size)
{ /* char is stored at left and paddind at cushion's right */
	int i = 0;
	char padd = ' ';

	UNUSED(accuracy);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	cushion[i++] = c;
	cushion[i] = '\0';

	if (width > 1)
	{
		cushion[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			cushion[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &cushion[0], 1) +
					write(1, &cushion[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &cushion[BUFF_SIZE - i - 1], width - 1) +
					write(1, &cushion[0], 1));
	}

	return (write(1, &cushion[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @cushion: Handles print [array]
 * @flags:  Calculates active flags
 * @width: get width.
 * @accuracy: accuracy specifier
 * @size: Size indicator
 *
 * Return: Sum of chars.
 */
int write_number(int is_negative, int ind, char cushion[],
	int flags, int width, int accuracy, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, cushion, flags, width, accuracy,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the cushion
 * @cushion: Cushion
 * @flags: Flags
 * @width: width
 * @prec: Accuracy specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char cushion[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && cushion[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && cushion[ind] == '0')
		cushion[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		cushion[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			cushion[i] = padd;
		cushion[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of cushion */
		{
			if (extra_c)
				cushion[--ind] = extra_c;
			return (write(1, &cushion[ind], length) + write(1, &cushion[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				cushion[--ind] = extra_c;
			return (write(1, &cushion[1], i - 1) + write(1, &cushion[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				cushion[--padd_start] = extra_c;
			return (write(1, &cushion[padd_start], i - padd_start) +
				write(1, &cushion[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		cushion[--ind] = extra_c;
	return (write(1, &cushion[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the cushion
 * @cushion: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @accuracy: Accuracy specifier
 * @size: Size indicator
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char cushion[],
	int flags, int width, int accuracy, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (accuracy == 0 && ind == BUFF_SIZE - 2 && cushion[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (accuracy > 0 && accuracy < length)
		padd = ' ';

	while (accuracy > length)
	{
		cushion[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			cushion[i] = padd;

		cushion[i] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of cushion [cushion>padd]*/
		{
			return (write(1, &cushion[ind], length) + write(1, &cushion[0], i));
		}
		else /* Asign extra char to left of padding [padd>cushion]*/
		{
			return (write(1, &cushion[0], i) + write(1, &cushion[ind], length));
		}
	}

	return (write(1, &cushion[ind], length));
}

/**
 * write_p_r - Write a memory address
 * @cushion: Arrays of chars
 * @ind: Index at which the number starts in the cushion
 * @length: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_p_r(char cushion[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			cushion[i] = padd;
		cushion[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of cushion */
		{
			cushion[--ind] = 'x';
			cushion[--ind] = '0';
			if (extra_c)
				cushion[--ind] = extra_c;
			return (write(1, &cushion[ind], length) + write(1, &cushion[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of cushion */
		{
			cushion[--ind] = 'x';
			cushion[--ind] = '0';
			if (extra_c)
				cushion[--ind] = extra_c;
			return (write(1, &cushion[3], i - 3) + write(1, &cushion[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				cushion[--padd_start] = extra_c;
			cushion[1] = '0';
			cushion[2] = 'x';
			return (write(1, &cushion[padd_start], i - padd_start) +
				write(1, &cushion[ind], length - (1 - padd_start) - 2));
		}
	}
	cushion[--ind] = 'x';
	cushion[--ind] = '0';
	if (extra_c)
		cushion[--ind] = extra_c;
	return (write(1, &cushion[ind], BUFF_SIZE - ind - 1));
}
