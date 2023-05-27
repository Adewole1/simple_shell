#include "shell.h"

/**
 * errToInt - Function to convert an error string to an integer
 *
 * @str: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int errToInt(char *str)
{
	int i = 0;
	unsigned long int reslt = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			reslt = reslt * 10;
			reslt = reslt + (str[i] - '0');
			if (reslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (reslt);
}

/**
 * shellPutFD - Function to write a  character to file descriptor
 *
 * @c: The character to write
 * @fd: The filedescriptor to write to
 *
 * Return: 1 for success, -1 for error.
 */
int shellPutFD(char c, int fd)
{
	static int p;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == NEG_BUFFER || p >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, p);
		p = 0;
	}
	if (c != NEG_BUFFER)
		buf[p++] = c;
	return (1);
}

/**
 * shellPutsFDCount - Function to count the characters
 * To print to file descriptor
 *
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int shellPutsFDCount(char *str, int fd)
{
	int i = 0;

	if (str == NULL)
		return (0);
	while (*str)
	{
		i += shellPutFD(*str++, fd);
	}
	return (i);
}

