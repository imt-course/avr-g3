#include <stdio.h>
#include <stdlib.h>
#include "Types.h"
#include "LinkedList.h"



void LinkedList_Print(const NodeType *head_ref) {
	const NodeType *current_node = head_ref;
	if (head_ref == NULL_PTR) {
		printf("List Is Empty");
	}
	while(current_node != NULL_PTR) {
		printf("%d, ", current_node->data);
		current_node = current_node->next;
	}
	printf("\n");
}


NodeType* LinkedList_Append(NodeType** head_ref, u32 data) {
	/* Reverse space for new_node*/
	NodeType *new_node = (NodeType*)malloc(sizeof(NodeType));
	/* Declaring current_node to iterate over all nodes */
	NodeType *current_node = *head_ref;
	/* Initializing new_node*/
	new_node->data = data;
	new_node->next = NULL_PTR;
	/* Check if Linked is empty */
	if (*head_ref == NULL_PTR) {
		*head_ref = new_node;
	}
	/* Iteration over all nodes to find the last one */
	while(current_node != NULL_PTR) {
		if (current_node->next == NULL_PTR) {
			/* Make last node next points to new node */
			current_node->next = new_node;
			break;
		}
		/* Point to new node */
		current_node = current_node->next;
	}
	return new_node;
}


void LinkedList_InsertFirst(NodeType** head_ref, u32 data) {
	/* Reverse space for new_node*/
	NodeType *new_node = (NodeType*)malloc(sizeof(NodeType));
	/* Initializing new_node*/
	new_node->data = data;
	new_node->next = *head_ref;
	/* Make the head points to new_node */
	*head_ref  = new_node;
}

NodeType* LinkedList_InsertAfter(NodeType** head_ref, NodeType* node, u32 data) {
	/* Reverse space for new_node*/
	NodeType *new_node = (NodeType*)malloc(sizeof(NodeType));
	/* Declaring current_node to iterate over all nodes */
	NodeType *current_node = *head_ref;
	/* Initializing new_node*/
	new_node->data = data;
	while(current_node != NULL_PTR) {
		if (current_node == node) {
			new_node->next = node->next;
			node->next = new_node;
			break;
		}
		else if (current_node->next == NULL_PTR) {
			current_node->next = new_node;
			new_node->next = NULL_PTR;
		}
		/* Point to new node */
		current_node = current_node->next;

	}
	return new_node;
}



void LinkedList_Sort(NodeType** head_ref) {
	u8 size = 0;
	u8 i, j;
	NodeType *current_node = *head_ref;
	NodeType *prev_node;
	while (current_node != NULL_PTR) {
		size++;
		current_node = current_node->next;
	}
	current_node = (*head_ref)->next;
	prev_node = *head_ref;
	for (i=size-1; i>0; i--) {
		current_node = (*head_ref)->next;
		prev_node = *head_ref;
		for (j=0; j<i; j++) {
			if (current_node->data < prev_node->data) {
				prev_node->next = current_node->next;
				current_node->next = (current_node->next)->next;
				(prev_node->next)->next = current_node;
				prev_node = prev_node->next;
			} else {
				prev_node = current_node;
				current_node = current_node->next;
			}
		}
	}

}


void LinkedList_Reverse(NodeType** head_ref) {
	
}



void LinkedList_DeleteNumber(NodeType** head_ref, u32 number) {
	/* Declaring current_node to iterate over all nodes */
	NodeType *current_node = (*head_ref)->next;
	NodeType *prev_node = *head_ref;
	while(current_node != NULL_PTR) {
		if (current_node->data == number) {
			prev_node->next = current_node->next;
			free(current_node);
			current_node = prev_node->next;
		}
		else {
			prev_node = current_node;
			current_node = current_node->next;
		}
	}
	if ((*head_ref)->data == number) {
		prev_node = *head_ref;
		*head_ref = (*head_ref)->next;
		free(prev_node);
	}

	/*
	NodeType *temp;
	while(current_node != NULL_PTR) {
		if (current_node->next == NULL_PTR) {
			break;
		}
		if ((current_node->next)->data == number) {
			temp = current_node->next;
			current_node->next = (current_node->next)->next;
			free(temp);
		}
		if ((current_node->next != NULL_PTR) && (current_node->next)->data != number) {
			current_node = current_node->next;
		}
	}
	if ((*head_ref)->data == number) {
		temp = *head_ref;
		*head_ref = (*head_ref)->next;
		free(temp);
	}
	*/
}



void LinkedList_DeleteNode(NodeType** head_ref, NodeType* node) {
	/* Declaring current_node to iterate over all nodes */
	NodeType *current_node = *head_ref;
	/* Check if node is NULL*/
	if (node == NULL_PTR) {
		/* Do Nothing */
	}
	else if (node == *head_ref) {
		*head_ref = node->next;
		free(node);
	}
	else {
		while (current_node != NULL_PTR) {
			/* Check if next node is the node to be deleted */
			if (current_node->next == node) {
				/* Point to the next of deleted node */
				current_node->next = node->next;
				/* Free node memory */
				free(node);
				break;
			}
			/* Point to new node */
			current_node = current_node->next;
		}
	}
}

void LinkedList_DeleteAll(NodeType** head_ref) {
	/* Declaring current_node to iterate over all nodes */
	NodeType *current_node = *head_ref;
	while (current_node != NULL_PTR) {
		/* Make head points to next node */
		*head_ref = current_node->next;
		/* Free node memory */
		free(current_node);
		/* Point to new node */
		current_node = *head_ref;

	}
}
