#include "shell.h"

/**
 * _myhistory - displays the history list.
 *
 * @info: Structure with the arguments.
 *
 *  Return: Success 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - creates an alias to a string
 * @info: parameter structure
 * @str: string alias
 *
 * Return: Success 0, otherwise 1 if there is an error
 */
int unset_alias(info_t *info, char *str)
{
	char *ptr, ch;
	int del;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	del = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = ch;
	return (del);
}

/**
 * set_alias - sets alias to string
 * @info: parameter structure
 * @str: string alias
 *
 * Return: 0 on success, 1 on an error
 */
int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: node to the alias
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *ptr = NULL, *val = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (val = node->str; val <= ptr; val++)
			_putchar(*val);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Does the same function as the alias builtin
 * @info: Structure containing the arguments.
 *
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
