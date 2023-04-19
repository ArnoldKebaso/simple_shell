#include "shell.h"

/**
 * _erratoi - string conversion to an integer
 * @str: string to be converted
 * Return: 0 if the string is empty, -1 on error
 *
 */
int _erratoi(char *str)
{
	int count = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (count = 0;  str[count] != '\0'; count++)
	{
		if (str[count] >= '0' && str[count] <= '9')
		{
			result *= 10;
			result += (str[count] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Displays an error message
 * @info: parameter & return info struct
 * @estr: stringwith the error type
 * Return: 0 if empty string, converted number otherwise -1 on error
 *
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal
 * @input:input
 * @fd:filedescriptor to write
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function
 * @val: number
 * @base: base integer
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int val, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = val;

	if (!(flags & CONVERT_UNSIGNED) && val < 0)
	{
		n = -val;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @reg: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *reg)
{
	int count;

	for (count = 0; reg[count] != '\0'; count++)
		if (reg[count] == '#' && (!count || reg[count - 1] == ' '))
		{
			reg[count] = '\0';
			break;
		}
}
