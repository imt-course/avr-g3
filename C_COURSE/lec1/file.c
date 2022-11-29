#include <stdio.h>


int main (void) {
	int num1, num2;
	int sum;
	printf("Please enter first number: ");
	scanf("%d", &num1);
	printf("Please enter second number: ");
	scanf("%d", &num2);
	sum = num1 + num2;
	printf("%d + %d = %d", num1, num2, sum);

}
