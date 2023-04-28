#include "shell.h"

/**
 * bfree - frees a pointer and makes the address to be null
 * @ptr: address of the pointer to free
 *
 * Return: 1 Success, 0 otherwise.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
