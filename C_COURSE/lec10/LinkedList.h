#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node {
	u32 data;
	struct node *next;
} NodeType;

void LinkedList_Print(const NodeType *head_ref);
NodeType* LinkedList_Append(NodeType** head_ref, u32 data);
void LinkedList_InsertFirst(NodeType** head_ref, u32 data);
NodeType* LinkedList_InsertAfter(NodeType** head_ref, NodeType* node, u32 data);
void LinkedList_Sort(NodeType** head_ref);
void LinkedList_Reverse(NodeType** head_ref);
void LinkedList_DeleteNumber(NodeType** head_ref, u32 number);
void LinkedList_DeleteNode(NodeType** head_ref, NodeType* node);
void LinkedList_DeleteAll(NodeType** head_ref);

#endif