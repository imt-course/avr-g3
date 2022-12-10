#include <stdio.h>
#include "math.h"

void isEven (int num);
void printName (void);
void swap (void);
int fib (int n);
int x = 10;
int y = 5;
void printBinary (int number);
int main (void) {
	/*
	int number, exponent, result;
	printf("Please enter number: ");
	scanf("%d", &number);
	printf("Please enter exponent: ");
	scanf("%d", &exponent);
	result = power(number, exponent);
	printf("Result = %d", result);
	*/
	/*
	printName();
	isEven(5);
	isEven(8);
	*/
	/*
	printf("x before = %d\n", x);
	printf("y before = %d\n", y);
	swap();
	
	call();
	//a;
	printf("x after = %d\n", x);
	printf("y after = %d\n", y);
	*/
	printBinary(367);
}
void printBinary (int number) {
	int i;
	printf("0b");
	for (i=31; i>=0; i--) {
		printf("%d", (number>>i)&1);
		
		if (i%4 == 0) {
			printf(" ");
		}
	}
	printf("\n");
}

int fib (int n) {
	if (n < 2) {
		return n;
	}
	else {
		return (fib(n-1) + fib(n-2));
	}
}


void swap (void) {
	int temp = x;
	x = y;
	y = temp;
}

void printName (void) {
	printf("Hassan\n");
}


void isEven (int num) {
	if (num%2 == 0) {
		printf("EVEN\n");
	}
	else {
		printf("ODD\n");
	}
}

