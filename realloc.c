#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@ptr: the pointer to the memory area
 *@by: the byte to fill the pointer
 *@a: the amount of bytes to be filled
 *Return: (ptr) a pointer to the memory area pointer
 */
char *_memset(char *ptr, char by, unsigned int a)
{
	unsigned int i;

	for (i = 0; i < a; i++)
		ptr[i] = by;
	return (ptr);
}

/**
 * ffree - frees a string
 * @str: the string of strings
 */
void ffree(char **str)
{
	char **ch = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(ch);
}

/**
 * _realloc - memory reallocation
 * @ptr: pointer to previous malloc'ated block
 * @old: byte size of previous block
 * @new: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old, unsigned int new)
{
	char *ch;

	if (!ptr)
		return (malloc(new));
	if (!new)
		return (free(ptr), NULL);
	if (new == old)
		return (ptr);

	ch = malloc(new);
	if (!ch)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		ch[old] = ((char *)ptr)[old];
	free(ptr);
	return (ch);
}
