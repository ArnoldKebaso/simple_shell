#include "shell.h"

/**
 * get_environ - string array copy from the environ
 * @info: Structure containing potential arguments
 *
 * Return: Success 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - deletes environment variable
 * @info: Structure containing arguments
 *.
 *  Return: 1 on success, 0 otherwise
 * @str: string env var property
 */
int _unsetenv(info_t *info, char *str)
{
	list_t *node = info->env;
	size_t i = 0;
	char *ch;

	if (!node || !str)
		return (0);

	while (node)
	{
		ch = starts_with(node->str, str);
		if (ch && *ch == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - initialize a new environment variable
 * @info: Structure with the arguments
 *
 * @var: the string env var property
 * @value: the string environment variable value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *reg = NULL;
	list_t *ptr;
	char *ch;

	if (!var || !value)
		return (0);

	reg = malloc(_strlen(var) + _strlen(value) + 2);
	if (!reg)
		return (1);
	_strcpy(reg, var);
	_strcat(reg, "=");
	_strcat(reg, value);
	ptr = info->env;
	while (ptr)
	{
		ch = starts_with(ptr->str, var);
		if (ch && *ch == '=')
		{
			free(ptr->str);
			ptr->str = reg;
			info->env_changed = 1;
			return (0);
		}
		ptr = ptr->next;
	}
	add_node_end(&(info->env), reg, 0);
	free(reg);
	info->env_changed = 1;
	return (0);
}
