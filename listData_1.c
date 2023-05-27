#include "shell.h"

/**
 * getListDataLen - Function to get the length of  list data
 *
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t getListDataLen(const list_data_struct *h)
{
	size_t j = 0;

	while (h != NULL)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * getListDataStr - Function to get an array of strings of the list data
 *
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **getListDataStr(list_data_struct *head)
{
	list_data_struct *node = head;
	size_t i = getListDataLen(head), j;
	char **str;
	char *s;

	if (head == NULL || !i)
		return (NULL);
	str = malloc(sizeof(char *) * (i + 1));
	if (str == NULL)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		s = malloc(strLength(node->str) + 1);
		if (s == NULL)
		{
			for (j = 0; j < i; j++)
				free(str[j]);
			free(str);
			return (NULL);
		}

		s = strCopy(s, node->str);
		str[i] = s;
	}
	str[i] = NULL;
	return (str);
}

/**
 * addListNode - Function to add a node to the start of the list data
 *
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_data_struct *addListNode(list_data_struct **head,
		const char *str, int num)
{
	list_data_struct *new_head;

	if (head == NULL)
		return (NULL);

	new_head = malloc(sizeof(list_data_struct));
	if (new_head == NULL)
		return (NULL);
	memFill((void *)new_head, 0, sizeof(list_data_struct));
	new_head->num = num;
	if (str)
	{
		new_head->str = strDup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * printListData - Function to print all elements of a list data
 *
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printListData(const list_data_struct *h)
{
	size_t j = 0;

	while (h != NULL)
	{
		shellPuts(toString(h->num, 10, 0));
		shellPutchar(':');
		shellPutchar(' ');
		shellPuts(h->str ? h->str : "(nil)");
		shellPuts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

