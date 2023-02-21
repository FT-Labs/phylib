#include "libphy.h"

/* Add data to the start of the linked list.  */
void llist_add_to(llist_t **old_head, void *data)
{
	llist_t *new_head = malloc(sizeof(llist_t));

	new_head->data = data;
	new_head->link = *old_head;
	*old_head = new_head;
}

/* Add data to the end of the linked list.  */
void llist_add_to_end(llist_t **list_head, void *data)
{
	while (*list_head)
		list_head = &(*list_head)->link;
	*list_head = calloc(sizeof(llist_t), 1);
	(*list_head)->data = data;
	/*(*list_head)->link = NULL;*/
}

/* Remove first element from the list and return it */
void* llist_pop(llist_t **head)
{
	void *data = NULL;
	llist_t *temp = *head;

	if (temp) {
		data = temp->data;
		*head = temp->link;
		free(temp);
	}
	return data;
}

/* Unlink arbitrary given element from the list */
void llist_unlink(llist_t **head, llist_t *elm)
{
	if (!elm)
		return;
	while (*head) {
		if (*head == elm) {
			*head = (*head)->link;
			break;
		}
		head = &(*head)->link;
	}
}

/* Recursively free all elements in the linked list.  If freeit != NULL
 * call it on each datum in the list */
void llist_free(llist_t *elm, void (*freeit)(void *data))
{
	while (elm) {
		void *data = llist_pop(&elm);

		if (freeit)
			freeit(data);
	}
}

/* Reverse list order. */
llist_t* llist_rev(llist_t *list)
{
	llist_t *rev = NULL;

	while (list) {
		llist_t *next = list->link;

		list->link = rev;
		rev = list;
		list = next;
	}
	return rev;
}

llist_t* llist_find_str(llist_t *list, const char *str)
{
	while (list) {
		if (strcmp(list->data, str) == 0)
			break;
		list = list->link;
	}
	return list;
}
