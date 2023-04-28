#include "shell.h"

/**
 * _strlen - string length
 * @str: the string to check
 *
 * Return: length of string
 */
int _strlen(char *str)
{
	int l = 0;

	if (!str)
		return (0);

	while (*str++)
		l++;
	return (l);
}

/**
 * _strcmp - performs a comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: - if str1 < str2, + if str1 > str2, 0 if str1 == str2
 */
int _strcmp(char *str1, char *sstr2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @atp: destination buffer
 * @buf: source buffer
 *
 * Return: pointer to atp
 */
char *_strcat(char *atp, char *buf)
{
	char *ch = atp;

	while (*atp)
		atp++;
	while (*buf)
		*atp++ = *buf++;
	*atp = *buf;
	return (ch);
}
