#include <stdio.h>

#define MAX_NUMBEER 10
#define ARR_LENGTH  6

int getMaxRepeatedNumber (int* arr, int arrSize, int* maxCount);

int main (void) {
	int arr[ARR_LENGTH] = {5,5,5,20,2,1};
	int count, num;
	num = getMaxRepeatedNumber(arr, ARR_LENGTH, &count);
	printf("Max repeated number is: %d\n", num);
	printf("Max count is: %d\n", count);
}

int getMaxRepeatedNumber (int* arr, int arrSize, int* maxCount) {
	int i,max = 0, num;
	int temp[MAX_NUMBEER] = {0};
	for (i=0; i<arrSize; i++) {
		temp[arr[i]]++;
		if (temp[arr[i]] > max) {
			max = temp[arr[i]];
			num = arr[i];
		}
	}
	*maxCount = max;
	return num;
}
