#include "shell.h"

/**
 * printError - prints an error message
 *
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
void printError(data_struct *info, char *estr)
{
	errorPuts(info->fname);
	errorPuts(": ");
	printDec(info->line_count, STDERR_FILENO);
	errorPuts(": ");
	errorPuts(info->argv[0]);
	errorPuts(": ");
	errorPuts(estr);
}

/**
 * errorPuts - Function to print an error input string
 *
 * @str: the error string to be printed
 *
 * Return: Nothing
 */
void errorPuts(char *str)
{
	int i = 0;

	if (str == NULL)
		return;
	while (str[i] != '\0')
	{
		errorPutchar(str[i]);
		i++;
	}
}

/**
 * errorPutchar - Function to write the character c to stderr
 *
 * @c: The character to write
 *
 * Return: 1 for success, -1 for error
 */
int errorPutchar(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == NEG_BUFFER || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != NEG_BUFFER)
		buf[i++] = c;
	return (1);
}

