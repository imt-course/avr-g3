#include <stdio.h>
#include "algorithms.h"

void BubbleSort (int arr[], int size) {
	int i, j;
	for (i=size-1; i>0; i--) {
		for (j=0; j<i; j++) {
			if (arr[j] > arr[j+1]) {
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}


int LinearSearch (const int arr[], int size, int number) {
	int i;
	for (i=0; i<size; i++) {
		if (arr[i] == number) {
			break;
		}
	}
	return i;
}

int BinarySearch (const int arr[], int size, int number) {
	int start = 0;
	int end = size - 1;
	int mid;
	int index = size;
	while (start <= end) {
		mid = (start + end) / 2;
		if (number == arr[mid]) {
			index = mid;
			break;
		}
		else if (number > arr[mid]) {
			start = mid+1;
		}
		else if (number < arr[mid]) {
			end = mid-1;
		}
	}
	return index;
}

void printArray (int arr[], int size) {
	int i;
	for (i=0; i<size; i++) {
		printf("%d ", arr[i]);
	}
}