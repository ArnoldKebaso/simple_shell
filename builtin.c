#include "shell.h"

/**
 * _myexit - Quits the shell
 * @info: struct with the arguments.
 *
 *  Return: exits with a given exit status
 *         (0) if info in argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int my_exit;

	if (info->argv[1])
	{
		my_exit = _erratoi(info->argv[1]);
		if (my_exit == -1)
		{
			info->status = 2;
			print_error(info, "Invalid digit: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - navigates into the directory of the process
 * @info: Structure containing potential arguments.
 *
 *  Return: Success 0
 */
int _mycd(info_t *info)
{
	char *ch, *cd, buffer[1024];
	int ch_cd;

	ch = getcwd(buffer, 1024);
	if (!ch)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		cd = _getenv(info, "HOME=");
		if (!cd)
			ch_cd =
				chdir((cd = _getenv(info, "PWD=")) ? cd : "/");
		else
			ch_cd = chdir(cd);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(ch);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		ch_cd =
			chdir((cd = _getenv(info, "OLDPWD=")) ? cd : "/");
	}
	else
		ch_cd = chdir(info->argv[1]);
	if (ch_cd == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **my_array;

	my_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*my_array);
	return (0);
}
