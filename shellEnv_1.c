#include "shell.h"

/**
 * shellEnv - Function to print the current environment
 *
 * @info: Structure containing arguments.
 *
 * Return: Always 0
 */
int shellEnv(data_struct *info)
{
	printStringList(info->env);
	return (0);
}

/**
 * getEnv - Function to get the string array copy of shell environ
 *
 * @info: Structure containing arguments.
 *
 * Return: Always 0
 */
char **getEnv(data_struct *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = getListDataStr(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * shellGetEnv - Function to get the value of an environment variable
 *
 * @info: Structure containing arguments.
 * @name: env var name
 *
 * Return: the value or NULL
 */
char *shellGetEnv(data_struct *info, const char *name)
{
	list_data_struct *node = info->env;
	char *c;

	while (node)
	{
		c = nodeStartsWith(node->str, name);
		if (c && *c)
			return (c);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnv - Create or modify environment variable,
 *
 * @info: Structure containing arguments.
 * @var: the string env var property
 * @value: the string env var value
 *
 *  Return: Always 0
 */
int setEnv(data_struct *info, char *var, char *value)
{
	char *buf = NULL;
	list_data_struct *node;
	char *c;

	if (!var || !value)
		return (0);

	buf = malloc(strLength(var) + strLength(value) + 2);
	if (!buf)
		return (1);
	strCopy(buf, var);
	strJoin(buf, "=");
	strJoin(buf, value);
	node = info->env;
	while (node)
	{
		c = nodeStartsWith(node->str, var);
		if (c && *c == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addListEndNode(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

