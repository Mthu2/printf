#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1
/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};
/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,
va_list list, char cushion[], int flags, int width, int accuracy, int size);

/**
 * Funtions to print chars and strings
 */
int print_char(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);
int print_string(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);
int print_percent(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);

/**
 * Functions to print numbers
 */
int print_int(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);
int print_binary(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);
int print_unsigned(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);
int print_octal(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);
int print_hexadecimal(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);
int print_hexa_upper(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);

int print_hexa(va_list types, char find_to[],
char cushion[], int flags, char flag_ch, int width, int accuracy, int size);

/*
 * Function to print non printable characters
 */
int print_n_p(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);

/*
 * Funcion to print memory address
 */
int print_p_r(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);

/**
 * Funciotns to handle other specifiers
 */
int obtain_flags(const char *format, int *i);
int obtain_width(const char *format, int *i, va_list list);
int obtain_accuracy(const char *format, int *i, va_list list);
int obtain_size(const char *format, int *i);

/**
 * Function to print string in reverse
 */
int print_reverse(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);

/**
 * Function to print a string in rot 13
 */
int print_rot13string(va_list types, char cushion[],
	int flags, int width, int accuracy, int size);

/**
 * width handler
 */
int handle_write_char(char c, char cushion[],
	int flags, int width, int accuracy, int size);
int write_number(int is_positive, int ind, char cushion[],
	int flags, int width, int accuracy, int size);
int write_num(int ind, char bff[], int flags, int width, int accuracy,
	int length, char padd, char extra_c);
int write_p_r(char cushion[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind,
char cushion[],
	int flags, int width, int accuracy, int size);

/**
 * UTILs
 */
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */
