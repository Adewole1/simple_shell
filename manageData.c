#include "shell.h"

/**
 * initData - Function to initialise a new data_struct struct
 *
 * @info: struct address
 * @av: argument vector
 *
 * Return: nothing
 */
void initData(data_struct *info, char **av)
{
	int j = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strSplit(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strDup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (j = 0; info->argv && info->argv[j]; j++)
			;
		info->argc = j;

		replaceTag(info);
		replaceVariables(info);
	}
}

/**
 * freeData - Function to free data_struct struct fields
 *
 * @info: struct address
 * @all: true if freeing all fields
 *
 * Return: nothing
 */
void freeData(data_struct *info, int all)
{
	freeStrings(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeListData(&(info->env));
		if (info->history)
			freeListData(&(info->history));
		if (info->tag)
			freeListData(&(info->tag));
		freeStrings(info->environ);
			info->environ = NULL;
		freePointer((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		shellPutchar(NEG_BUFFER);
	}
}

/**
 * clearData - Function to free data_struct struct
 *
 * @info: struct address
 *
 * Return: nothing
 */
void clearData(data_struct *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

