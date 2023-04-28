#include "shell.h"

/**
 * _strcpy - copies a string
 * @atp: the destination
 * @buf: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *atp, char *buf)
{
	int j = 0;

	if (atp == buf || buf == 0)
		return (atp);
	while (buf[j])
	{
		atp[j] = buf[j];
		j++;
	}
	atp[j] = 0;
	return (atp);
}

/**
 * _strdup - duplicates a string
 * @ptr: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *ptr)
{
	int l = 0;
	char *ch;

	if (ptr == NULL)
		return (NULL);
	while (*ptr++)
		l++;
	ch = malloc(sizeof(char) * (l + 1));
	if (!ch)
		return (NULL);
	for (l++; l--;)
		ch[l] = *--ptr;
	return (ch);
}

/**
 *_puts - prints an input string
 *@ptr: the string to be printed
 *
 * Return: NULL
 */
void _puts(char *ptr)
{
	int n = 0;

	if (!ptr)
		return;
	while (ptr[n] != '\0')
	{
		_putchar(ptr[n]);
		n++;
	}
}

/**
 * _putchar - writes c to the standard output
 * @c: The character
 *
 * Return: On success 1, -1 on error
 * 
 */
int _putchar(char c)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}
