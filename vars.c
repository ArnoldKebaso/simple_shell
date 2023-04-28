#include "shell.h"

/**
 * is_chain - test if character in reg is a chain delimeter
 * @info: parameter structure
 * @reg: buffer
 * @atp: address of position in reg
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *reg, size_t *atp)
{
	size_t j = *atp;

	if (reg[j] == '|' && reg[j + 1] == '|')
	{
		reg[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (reg[j] == '&' && reg[j + 1] == '&')
	{
		reg[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (reg[j] == ';') /* found end of this command */
	{
		reg[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*atp = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @reg: the char buffer
 * @atp: address of current position in buf
 * @a: starting position in buf
 * @len: length of reg
 *
 * Return: Void
 */
void check_chain(info_t *info, char *reg, size_t *atp, size_t i, size_t len)
{
	size_t k = *atp;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			reg[a] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			reg[a] = 0;
			k = len;
		}
	}

	*atp = k;
}

/**
 * replace_alias - replaces an alias
 * @info: parameter structure
 *
 * Return: 1 if success, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int o;
	list_t *atp;
	char *ch;

	for (o = 0; o < 10; o++)
	{
		atp = node_starts_with(info->alias, info->argv[0], '=');
		if (!atp)
			return (0);
		free(info->argv[0]);
		ch = _strchr(atp->str, '=');
		if (!ch)
			return (0);
		ch = _strdup(ch + 1);
		if (!ch)
			return (0);
		info->argv[0] = ch;
	}
	return (1);
}

/**
 * replace_vars - replaces variables
 * @info: parameter structure
 *
 * Return: 1 if success, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int o = 0;
	list_t *atp;

	for (o = 0; info->argv[o]; o++)
	{
		if (info->argv[o][0] != '$' || !info->argv[o][1])
			continue;

		if (!_strcmp(info->argv[o], "$?"))
		{
			replace_string(&(info->argv[o]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[o], "$$"))
		{
			replace_string(&(info->argv[o]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		atp = node_starts_with(info->env, &info->argv[o][1], '=');
		if (atp)
		{
			replace_string(&(info->argv[o]),
				_strdup(_strchr(atp->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[o], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
