#include "shell.h"

/**
 * **strtow - splits a string into words
 * @ptr: input string
 * @d: delimeter string
 * Return: a pointer to an array, NULL on an error
 */

char **strtow(char *ptr, char *d)
{ 
	int i, j, k, z, split = 0;
	char **s;

	if (ptr == NULL || ptr[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; ptr[i] != '\0'; i++)
		if (!is_delim(ptr[i], d) && (is_delim(ptr[i + 1], d) || !ptr[i + 1]))
			split++;

	if (split == 0)
		return (NULL);
	s = malloc((1 + split) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < split; j++)
	{
		while (is_delim(ptr[i], d))
			i++;
		k = 0;
		while (!is_delim(ptr[i + k], d) && ptr[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < k; z++)
			s[j][z] = ptr[i++];
		s[j][z] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @ptr: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *ptr, char d)
{
	int i, j, k, m, split = 0;
	char **s;

	if (ptr == NULL || ptr[0] == 0)
		return (NULL);
	for (i = 0; ptr[i] != '\0'; i++)
		if ((ptr[i] != d && ptr[i + 1] == d) ||
		    (ptr[i] != d && !ptr[i + 1]) || ptr[i + 1] == d)
			split++;
	if (split == 0)
		return (NULL);
	s = malloc((1 + split) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < split; j++)
	{
		while (ptr[i] == d && ptr[i] != d)
			i++;
		k = 0;
		while (ptr[i + k] != d && ptr[i + k] && ptr[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < k; z++)
			s[j][z] = ptr[i++];
		s[j][z] = 0;
	}
	s[j] = NULL;
	return (s);
}
