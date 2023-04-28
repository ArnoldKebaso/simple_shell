#include "shell.h"

/**
 * list_len - determines length of linked list
 * @ptr: pointer to the node
 *
 * Return: list size
 */
size_t list_len(const list_t *ptr)
{
	size_t k = 0;

	while (ptr)
	{
		ptr = ptr->next;
		k++;
	}
	return (k);
}

/**
 * list_to_strings - returns an array of strings
 * @h: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *h)
{
	list_t *atp = h;
	size_t k = list_len(h), j;
	char **atp;
	char *ptr;

	if (!h || !k)
		return (NULL);
	atp = malloc(sizeof(char *) * (k + 1));
	if (!atp)
		return (NULL);
	for (i = 0; atp; atp = atp->next, k++)
	{
		ptr = malloc(_strlen(atp->ptr) + 1);
		if (!ptr)
		{
			for (j = 0; j < k; j++)
				free(atp[j]);
			free(atp);
			return (NULL);
		}

		ptr = _strcpy(ptr, atp->ptr);
		atp[k] = ptr;
	}
	atp[k] = NULL;
	return (atp);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @atp: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *atp, char *prefix, char c)
{
	char *p = NULL;

	while (atp)
	{
		p = starts_with(atp->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (atp);
		atp = atp->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @h: pointer to list head
 * @atp: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *h, list_t *atp)
{
	size_t i = 0;

	while (h)
	{
		if (h == atp)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}
