#include "shell.h"

/**
 * hsh - main shell loop
 * @info: infomation structure
 * @argv: argument vector
 *
 * Return: 0 success, 1 otherwise
 */
int hsh(info_t *info, char **argv)
{
	ssize_t size = 0;
	int builtin_ret = 0;

	while (size != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		size = get_input(info);
		if (size != -1)
		{
			set_info(info, argv);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - searches for a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if error,
 *			0 if success,
 *			1 builtin found but with an error,
 *			-2 if builtin exits
 */
int find_builtin(info_t *info)
{
	int r, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (r = 0; builtintbl[r].type; r++)
		if (_strcmp(info->argv[0], builtintbl[r].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[r].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in a path
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *cd = NULL;
	int m, n;

	info->cd = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (m = 0, n = 0; info->arg[m]; m++)
		if (!is_delim(info->arg[m], " \t\n"))
			n++;
	if (!n)
		return;

	cd = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (find_cmd)
	{
		info->cd = cd;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec system call
 * @info: the infomation structure
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
