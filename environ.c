#include "shell.h"

/**
 * print_env - prints current working environment vars.
 * @info: Structure holding fields to be used as arguments.
 * Return: Always 0
 */
int print_env(info_t *info)
{
	print_env_lst(info->env);
	return (0);
}

/**
 * sh_getenv - retrieves value an environ variable
 * @info: Structure holding fields to be used as arguments
 * @name: environ variable name
 * Return: pointer to env var
 */
char *sh_getenv(info_t *info, const char *name)
{
	char *ptr;
	list_t *node = info->env;

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
 * sh_setenv - sets new or modifies environ variable
 * @info: Structure holding fields to be used as arguments
 * Return: Always 0
 */
int sh_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect numberr of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * sh_unsetenv - removes an environ variable
 * @info: Structure holding fields to be used as arguments
 * Return: Always 0
 */
int sh_unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * collect_env_list - collects a list of environ var
 * @info: Structure holding fields to be used as arguments
 * Return: Always 0
 */
int collect_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
