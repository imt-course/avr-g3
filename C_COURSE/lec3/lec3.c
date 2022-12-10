#include <stdio.h>

int main (void) {
	
	/********************** LAB 1 **********************/
	/*
	char i=0;
	while (i<10) {
		printf("%d\n", i);
		i++;
	}
	*/
	
	/********************** LAB 2 **********************/
	/*
	// Infinite Loop
	int i=1;
	while (i != 10) {
		printf("%d\n", i);
		i+=2;
	}
	*/
	/********************** LAB 3 **********************/
	/*
	int x;
	printf("Please enter 3x4 = ");
	scanf("%d", &x);
	while(x != 12) {
		printf("Wrong Answer, try again: ");
		scanf("%d", &x);
	}
	printf("Correct Answer");
	*/
	
	/********************** LAB 4 **********************/
	/*
	int num, i=1;
	printf("Please enter number: ");
	scanf("%d", &num);
	printf("Table is:\n");
	while (i < 13) {
		printf("%dx%d=%d\n", num, i, num*i);
		i++;
	}
	*/

	/********************** LAB 5 **********************/
	/*
	int num, factorial=1;
	printf("Please enter number: ");
	scanf("%d", &num);
	while (num > 0) {
		factorial *= num;
		num--;
	}
	printf("Factorial is: %d", factorial);
	*/

	/********************** LAB 6 **********************/
	/*
	int num, count=0;
	printf("Please enter number: ");
	scanf("%d", &num);
	do {
		num /= 10;
		count++;
	}while (num > 0);
	printf("Number of Digits is: %d", count);
	*/

	/********************** LAB 7 **********************/
	/*
	int num, count=0;
	printf("Please enter number: ");
	scanf("%d", &num);
	do {
		//num /= 2;
		num >>= 1;
		count++;
	}while (num > 0);
	printf("Number of Bits is: %d", count);
	*/
	
	/********************** LAB 8 **********************/
	/*
	int num, reversed = 0;
	printf("Please enter number: ");
	scanf("%d", &num);
	while (num > 0) {
		reversed = reversed*10 + num%10;
		num /= 10;
	}
	printf("Number reversed is: %d", reversed);
	*/

	/********************** LAB 9 **********************/
	/*
	int num, sum = 0;
	int i, n;
	printf("Enter Number Of Iterations : ");
	scanf("%d", &n);
	for (i=1; i<=n; i++) {
		printf("Enter Number %d: ", i);
		scanf("%d", &num);
		sum += num;
	}
	printf("Sum = %d\n", sum);
	printf("Avg = %.2f\n", (float)sum/n);
	*/
	
	/********************** LAB 10 **********************/
	/*
	int num, sum = 0;
	int i, n;
	printf("Enter Number Of Iterations : ");
	scanf("%d", &n);
	for (i=1; i<=n; i++) {
		printf("Enter Number %d: ", i);
		scanf("%d", &num);
		if (num < 0) {
			break;
		}
		sum += num;
	}
	printf("Sum = %d\n", sum);
	printf("Avg = %.2f\n", (float)sum/(i-1));
	*/
	
	/********************** LAB 11 **********************/
	/*
	int num, sum = 0;
	int i, n;
	printf("Enter Number Of Iterations : ");
	scanf("%d", &n);
	for (i=1; i<=n; i++) {
		printf("Enter Number %d: ", i);
		scanf("%d", &num);
		if (num < 0) {
			i--;
			continue;
		}
		sum += num;
	}
	printf("Sum = %d\n", sum);
	printf("Avg = %.2f\n", (float)sum/n);
	*/
	
	/********************** LAB 12 **********************/
	/*
	int num, reversed = 0;
	int i;
	printf("Please enter number: ");
	scanf("%d", &num);
	for (i=0; i<8; i++) {
		reversed = (reversed<<1) + (num&1);
		num >>= 1;
	}
	printf("Number reversed is: %d", reversed);
	*/
	
	/********************** LAB 12 **********************/
	//   x1,x2,x3
	// 0 ,1 ,1 , 2, 3, 5, 8, 13, 21, 34, ...
	int i,n;
	int x1 = 0;
	int x2 = 1;
	int x3 = x1 + x2;
	printf("Please enter a number: ");
	scanf("%d", &n);
	printf("%d, ", x1);
	if (n > 1) {
		printf("%d, ", x2);
	}
	if (n > 2) {
		printf("%d, ", x3);
	}
	for (i=3;i<n;i++) {
		x1 = x2;
		x2 = x3;
		x3 = x1 + x2;
		printf("%d, ", x3);
	}
	




}