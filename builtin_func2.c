#include "shell.h"

/**
 * unset_alias - unsets alias
 * @info: Structure holding fields to be used as arguments
 * @str: alias string
 * Return: 0 on success, 1 otherwirse
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int i;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	i = delete_node_at(&(info->alias),
			get_node_at(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (i);
}

/**
 * set_alias - sets alias to string
 * @info: Structure holding fields to be used as
 * arguments
 * @str: alias string
 * Return: 0 on success, 1 otherwise
 */
int set_alias(info_t *info, char *str)
{
	char *g;

	g = _strchr(str, '=');
	if (!g)
		return (1);
	if (!*++g)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * sh_history - displays the history list.
 * @info: Structure holding fields to be used as
 * arguments
 * Return: Always 0
 */
int sh_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * print_alias - prints a string of aliases
 * @node: the alias node
 * Return: 0 on success, 1 on error
 */

print_alias(list_t *node)
{
	char *p = NULL, *g = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (g = node->str; g <= p; g++)
			_putchar(*g);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * sh_alias - mimics the alias builtin
 * @info: Structure holds fields to be used as
 * arguments
 * Return: Always 0
 */
int sh_alias(info_t *info)
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
			print_alias(node_starts_at(info->alias, info->argv[i], '='));
	}
	return (0);
}
