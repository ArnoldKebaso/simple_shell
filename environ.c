#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure that has the arguments.
 *
 * Return: Success 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Returns the environ value
 * @info: Structure with the arguments.
 * @name: environ variable name
 *
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new envr var.
 *
 * @info: Structure containing arguments.
 *
 *  Return: Success 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Deletes environment variable
 * @info: Structure with the arguments.
 *
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int count;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (count = 1; count <= info->argc; count++)
		_unsetenv(info, info->argv[count]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t count;

	for (count = 0; environ[count]; count++)
		add_node_end(&node, environ[count], 0);
	info->env = node;
	return (0);
}
