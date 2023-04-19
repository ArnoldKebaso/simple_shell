#include "shell.h"

/**
 *_eputs - input string
 * @str: string to print
 *
 * Return: NULL
 */
void _eputs(char *str)
{
	int count = 0;

	if (!str)
		return;
	while (str[count] != '\0')
	{
		_eputchar(str[count]);
		count++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int count;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(2, buf, count);
		count = 0;
	}
	if (c != BUF_FLUSH)
		buf[count++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int count;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(fd, buf, count);
		count = 0;
	}
	if (c != BUF_FLUSH)
		buf[count++] = c;
	return (1);
}

/**
 *_putsfd - input string
 * @str: the string to print
 * @fd: filedescriptor to write
 *
 * Return: number of chars put
 */
int _putsfd(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		count += _putfd(*str++, fd);
	}
	return (count);
}
