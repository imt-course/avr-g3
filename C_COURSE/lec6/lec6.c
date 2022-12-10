#include <stdio.h>

int main (void) {
	/*
	int * ptr1 = (int*)2000;
	int * ptr2 = (int*)1000;
	int *ptr = ptr2-ptr1;
	printf("%d\n", ptr);
	*/
	/*
	int arr[5] = {1,2,3,4,5};
	int *ptr;
	ptr = arr;
	printf("ptr = %p\n", ptr);
	printf("arr = %p\n", arr);
	printf("&arr[0] = %p\n", &arr[0]);
	printf("++ptr = %p\n", ++ptr);
	*/
	
	/*
	int arr[10] = {0,5,7,9,15,20,6,7,8,9};
	int *ptr;
	ptr = arr; //Assume 1st element at 1000
	printf("%d \n", *(++ptr)); // 5 
	printf("%d \n", *ptr); // 0
	printf("%p \n", arr); // 1000
	printf("%d \n", *arr + 2); // 2
	printf("%d \n", *(arr + 2)); // 7
	printf("%d \n", arr[0]); // 0
	printf("%d \n", &arr[0]); // 1000
	printf("%d \n", 0[arr]); //  0
	printf("%d \n", arr++); // Error
	printf("%p \n", ptr); // 1000
	printf("%d \n", *ptr); // 0
	printf("%d \n", ptr[0]); // 0
	printf("%d \n", &ptr[0]); // 1000
	printf("%d \n", 0[ptr]); // 0
	*/
	
	char *array[] = {"Array", "Of", "Values"};
	printf("%d", sizeof(array));


}
