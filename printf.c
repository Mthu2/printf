#include "main.h"

void print_cushion(char cushion[], int *cush_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, accuracy, size, cush_ind = 0;
	va_list list;
	char cushion[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			cushion[cush_ind++] = format[i];
			if (cush_ind == BUFF_SIZE)
				print_cushion(cushion, &cush_ind);
			printed_chars++;
		}
		else
		{
			print_cushion(cushion, &cush_ind);
			flags = obtain_flags(format, &i);
			width = obtain_width(format, &i, list);
			accuracy = obtain_accuracy(format, &i, list);
			size = obtain_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, cushion,
				flags, width, accuracy, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_cushion(cushion, &cush_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_cushion - Prints the contents of the cushion if it exist
 * @cushion: Array of chars
 * @cush_ind: Index at which to add next char, represents the length.
 */
void print_cushion(char cushion[], int *cush_ind)
{
	if (*cush_ind > 0)
		write(1, &cushion[0], *cush_ind);

	*cush_ind = 0;
}
