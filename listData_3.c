#include "shell.h"

/**
 * freeListData - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void freeListData(list_data_struct **head_ptr)
{
	list_data_struct *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 * printStringList - Function to print only the str element
 * of a list_data_struct linked list
 *
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printStringList(const list_data_struct *h)
{
	size_t j = 0;

	while (h != NULL)
	{
		shellPuts(h->str ? h->str : "(nil)");
		shellPuts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

