#include "shell.h"

/**
 * shellSetEnv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int shellSetEnv(data_struct *info)
{
	if (info->argc != 3)
	{
		errorPuts("Incorrect number of arguements\n");
		return (1);
	}
	if (setEnv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * shellUnsetEnv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int shellUnsetEnv(data_struct *info)
{
	int i;

	if (info->argc == 1)
	{
		errorPuts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unSetEnv(info, info->argv[i]);

	return (0);
}

/**
 * unSetEnv - Remove an environment variable
 *
 * @info: Structure containing arguments.
 * @var: variable to remove
 *
 * Return: 1 on successful delete, else 0
 */
int unSetEnv(data_struct *info, char *var)
{
	list_data_struct *node = info->env;
	size_t j = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = nodeStartsWith(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = deleteIndexNode(&(info->env), j);
			j = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * shellPopulateEnv - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int shellPopulateEnv(data_struct *info)
{
	list_data_struct *node = NULL;
	size_t p;

	for (p = 0; environ[p]; p++)
		addListEndNode(&node, environ[p], 0);
	info->env = node;
	return (0);
}
