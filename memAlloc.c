#include "shell.h"

/**
 * reAlloc - Function to reallocate a block of memory
 *
 * @ptr: pointer to previous allocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the memory block.
 */
void *reAlloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *s;

	if (ptr == NULL)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	s = malloc(new_size);
	if (s == NULL)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		s[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (s);
}

/**
 * freePointer - Function to free a pointer
 *
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, else 0.
 */
int freePointer(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * memFill - Function to fill memory block with a constant byte
 *
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 *
 * Return: (s) a pointer to the memory area s
 */
char *memFill(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;

	return (s);
}

/**
 * freeStrings - Function to free a string of strings
 *
 * @pp: string of strings
 *
 * Return: nothing
 */
void freeStrings(char **pp)
{
	char **p = pp;

	if (pp == NULL)
		return;
	while (*pp != NULL)
		free(*pp++);

	free(p);
}
