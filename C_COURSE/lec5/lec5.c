#include <stdio.h>
#include "algorithms.h"

int main (void) {
	/*
	int i;
	int arr[5] = {1,2,3,4,5};
	printf("Please enter 5 numbers: \n");
	for (i=0; i<5; i++) {
		scanf("%d", &arr[i]);
	}
	printf("Numbers reversed are: \n");
	for (i=4; i>=0; i--) {
		printf("%d\n", arr[i]);
	}
	*/
	/*
	int i;
	int arr[] = {9,7,4,2};
	BubbleSort(arr, 4);
	for (i=0; i<4; i++) {
		printf("%d ", arr[i]);
	}
	*/
	
	/*
	int arr[] = {9,7,4,2,8,10,12,15,7};
	int index;
	index = LinearSearch(arr, 9, 0);
	if (index == 9) {
		printf("Not Exist");
	}
	else {
		printf("Exist at index %d ", index);
	}
	*/
	/*
	int arr[] = {9,7,4,2,8,10,12,15,7};
	int index;
	BubbleSort(arr, 9);
	printf("Array after sort: \n");
	printArray(arr, 9);
	index = BinarySearch(arr, 9, 12);
	if (index == 9) {
		printf("Not Exist");
	}
	else {
		printf("Exist at index %d ", index);
	}
	*/
	
	/*
	char name[100];
	char str[] = "Ahmed";
	printf("Size = %d\n", sizeof(str));
	printf("Enter your name: ");
	scanf("%s", name);
	printf("Welcome %s\n", name);
	printf("Enter your name: ");
	scanf("%s", name);
	printf("Welcome %s\n", name);
	*/
	
	int arr[5][3] = {{2,4,7}, {5,3,2}};
	printf("Size = %d\n", sizeof(arr[0]));
	arr[7][1] = 20;
	printf("%d", arr[7][1]);


}