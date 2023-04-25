#include "shell.h"

/**
 **_strncpy - copies a string
 *@ptr: the destination string to be copied to
 *@atp: the source string
 *@c: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *ptr, char *atp, int c)
{
	int i, j;
	char *st = ptr;

	i = 0;
	while (atp[i] != '\0' && i < c - 1)
	{
		ptr[i] = atp[i];
		i++;
	}
	if (i < c)
	{
		j = i;
		while (j < c)
		{
			ptr[j] = '\0';
			j++;
		}
	}
	return (st);
}

/**
 **_strncat - concatenates two strings
 *@ptr: the first string
 *@atp: the second string
 *@c: the amount of bytes
 *Return: the concatenated string
 */
char *_strncat(char *ptr, char *atp, int c)
{
	int i, j;
	char *st = ptr;

	i = 0;
	j = 0;
	while (ptr[i] != '\0')
		i++;
	while (atp[j] != '\0' && j < c)
	{
		ptr[i] = atp[j];
		i++;
		j++;
	}
	if (j < c)
		ptr[i] = '\0';
	return (st);
}

/**
 **_strchr - locates a character in a string
 *@st: the string to be parsed
 *@ch: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *st, char ch)
{
	do {
		if (*st == ch)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
