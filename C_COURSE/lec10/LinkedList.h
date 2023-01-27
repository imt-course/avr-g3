#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef u32 LinkedListDataType;

typedef struct node {
	LinkedListDataType data;
	struct node *next;
} NodeType;

void LinkedList_Print(const NodeType *head_ref);
NodeType* LinkedList_Append(NodeType** head_ref, LinkedListDataType data);
void LinkedList_InsertFirst(NodeType** head_ref, LinkedListDataType data);
NodeType* LinkedList_InsertAfter(NodeType** head_ref, NodeType* node, u32 data);
void LinkedList_Sort(NodeType** head_ref);
void LinkedList_Reverse(NodeType** head_ref);
void LinkedList_DeleteNumber(NodeType** head_ref, LinkedListDataType number);
void LinkedList_DeleteNode(NodeType** head_ref, NodeType* node);
void LinkedList_DeleteAll(NodeType** head_ref);

#endif