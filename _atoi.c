#include "shell.h"

/**
 * interactive - If the shell is in interactive mode it returns true
 * @info: struct address
 *
 * Return: success 1 if it is in interactive mode, 0 if it fails
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - function to check if it is a delimiter
 * @c: character to check
 * @delim: string delimiter
 * Return: success 1 if true, fail 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - looks into alphabet letters
 *@c: character to take in at stdin
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int count, sign = 1, flag = 0, ptr;
	unsigned int answer = 0;

	for (count = 0;  s[count] != '\0' && flag != 2; count++)
	{
		if (s[count] == '-')
			sign *= -1;

		if (s[count] >= '0' && s[count] <= '9')
		{
			flag = 1;
			answer *= 10;
			answer += (s[count] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		ptr = -answer;
	else
		ptr = answer;

	return (ptr);
}
