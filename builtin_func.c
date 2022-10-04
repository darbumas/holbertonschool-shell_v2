#include "shell.h"

/**
 * sh_exit - exit the shell
 * @info: Structure holds potential arguments.
 * Return: exit status if info.argv[0] != "exit"
 */
int sh_exit(info_t *info)
{
	int flag;

	if (info->argv[1])
	{
		flag = _erratoi(info->argv[1]);
		if (flag == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
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
 * sh_cdir - changes the current directory of the process
 * @info: Structure holding potential arguments.
 * Return: Always 0
 */
int sh_cdir(info_t *info)
{
	char *s, *dir, buffer[1024];
	int ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			ret = /* what to do? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		ret = /* what to do? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		ret = chdir(info->argv[1]);
	if (ret == -1)
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
 * sh_help - changes current directory of the process
 * @info: Structure holding potential arguments
 * Return: Always 0
 */
int sh_help(info_t *info)
{
	char **args;

	args = info->argv;
	_puts("ATTN: help call received; function not yet implemented \n");
	if (0)
		_puts(*args);
	return (0);
}
