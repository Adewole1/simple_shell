#include "shell.h"

/**
 * getNodeStartswith - Function to get node whose string starts with prefix
 *
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_data_struct *getNodeStartswith(list_data_struct *node,
		char *prefix, char c)
{
	char *ptr = NULL;

	while (node != NULL)
	{
		ptr = nodeStartsWith(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getIndexNode - Function to get the index of a node
 *
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node
 */
ssize_t getIndexNode(list_data_struct *head, list_data_struct *node)
{
	size_t i = 0;

	while (head != NULL)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * addListEndNode - Function to add a node to the end of the list
 *
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_data_struct *addListEndNode(list_data_struct **head,
		const char *str, int num)
{
	list_data_struct *new_node, *node;

	if (head == NULL)
		return (NULL);
	node = *head;

	new_node = malloc(sizeof(list_data_struct));
	if (new_node == NULL)
		return (NULL);
	memFill((void *)new_node, 0, sizeof(list_data_struct));
	new_node->num = num;

	if (str)
	{
		new_node->str = strDup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * deleteIndexNode - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deleteIndexNode(list_data_struct **head, unsigned int index)
{
	list_data_struct *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

