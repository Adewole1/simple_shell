#include "shell.h"

/**
 * main - Program starting point
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	data_struct info[] = { DATA_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				errorPuts(argv[0]);
				errorPuts(": 0: Unable to open ");
				errorPuts(argv[1]);
				errorPutchar('\n');
				errorPutchar(NEG_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	shellPopulateEnv(info);
	readShellHistory(info);
	shellMainloop(info, argv);
	return (EXIT_SUCCESS);
}
