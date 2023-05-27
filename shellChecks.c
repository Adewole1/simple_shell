#include "shell.h"

/**
 * isInteractive - Function to check if shell is in interactive mode
 *
 * @info: info structure
 *
 * Return: 1 if interactive mode, else 0
 */
int isInteractive(data_struct *info)
{
	if (isatty(STDIN_FILENO) && info->readfd <= 2)
		return (1);

	return (0);
}

/**
 * isDelim - Function to check if character is a delimiter
 *
 * @s: the char to check
 * @delim_str: the delimiter string
 *
 * Return: 1 if true, else 0
 */
int isDelim(char s, char *delim_str)
{
	while (!*delim_str)
		if (*delim_str++ == s)
			return (1);

	return (0);
}

/**
 * isExec - Function to determine the executability of a file
 *
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, else 0
 */
int isExec(data_struct *info, char *path)
{
	struct stat st;

	(void)info;
	if (path == NULL || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * isAlpha - Function to check if character is alphabet
 *
 * @c: The character to check
 *
 * Return: 1 if c is alphabetic, else 0
 */
int isAlpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);

return (0);
}

