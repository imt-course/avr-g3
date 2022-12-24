#include <stdio.h>
#include <stdlib.h>
#include "Types.h"
#include "LinkedList.h"



void* reallocate(void* ptr_old, u32 old_size, u32 new_size);



int main (void) {
	NodeType *head = NULL_PTR;
	NodeType *temp = NULL_PTR;
	temp = LinkedList_Append(&head, 2); // 2
	LinkedList_Append(&head, 3); // 2 3
	LinkedList_InsertAfter(&head, temp, 8); // 2 8 3
	LinkedList_Append(&head, 5); // 2 8 3 5
	LinkedList_InsertFirst(&head, 1); // 1 2 8 3 5
	temp = LinkedList_Append(&head, 10); // 1 2 8 3 5 10
	LinkedList_Append(&head, 15); // 1 2 8 3 5 10 15
	LinkedList_DeleteNode(&head, temp); // 1 2 8 3 5 15
	LinkedList_Print(head);
	LinkedList_DeleteAll(&head);
	LinkedList_Print(head);

	
	
	
	
	
	
	/*
	u32 *ptr = NULL_PTR;
	u32 n, i, sum=0;
	printf("Please enter number of elements: ");
	scanf("%d", &n);
	ptr = (u32*)malloc(n*sizeof(u32));
	for (i=0; i<n; i++) {
		scanf("%d", (ptr+i));
	}
	printf("You entered: ");
	for (i=0; i<n; i++) {
		printf("%d ", ptr[i]);
		sum += ptr[i];
	}
	printf("\nSum = %d\n", sum);
	free(ptr);
	*/
	/*
	u32 *ptr = NULL_PTR;
	u32 n, i, sum=0;
	printf("Please enter number of elements: ");
	scanf("%d", &n);
	ptr = (u32*)calloc(n,sizeof(u32));
	for (i=0; i<n; i++) {
		scanf("%d", (ptr+i));
	}
	printf("You entered: ");
	for (i=0; i<n; i++) {
		printf("%d ", ptr[i]);
		sum += ptr[i];
	}
	printf("\nSum = %d\n", sum);
	free(ptr);
	*/
	
	/*
	u32 *ptr = NULL_PTR;
	u32 n, i, sum=0;
	printf("Please enter number of elements: ");
	scanf("%d", &n);
	ptr = (u32*)malloc(n*sizeof(u32));
	for (i=0; i<n; i++) {
		scanf("%d", (ptr+i));
	}
	printf("You entered: ");	
	for (i=0; i<n; i++) {
		printf("%d ", ptr[i]);
		sum += ptr[i];
	}
	printf("\nptr before = %p\n", ptr);
	//ptr = (u32*)reallocate(ptr, n*sizeof(u32), n*sizeof(u32)+8);
	ptr = (u32*)realloc(ptr, n*sizeof(u32)+8);
	printf("ptr before = %p\n", ptr);
	printf("You entered: ");	
	for (i=0; i<n+2; i++) {
		printf("%d ", ptr[i]);
		sum += ptr[i];
	}

	printf("\nSum = %d\n", sum);
	free(ptr);
	*/

}


void* reallocate(void* ptr_old, u32 old_size, u32 new_size) {
	u8 i;
	void* ptr_new = malloc(new_size);
	for (i=0; i<old_size; i++) {
		*((u8*)ptr_new+i) = *((u8*)ptr_old+i);
	}
	free(ptr_old);
	return ptr_new;
}

