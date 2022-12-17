#include <stdio.h>
#include "Types.h"

void func (void);
extern u8 x;
int main (void) {	
	/*
	printf("Size of char = %d\n", sizeof(char));
	printf("Size of short int = %d\n", sizeof(short int));
	printf("Size of int = %d\n", sizeof(int));
	printf("Size of long int = %d\n", sizeof(long int));
	printf("Size of long long int = %d\n", sizeof(long long int));
	printf("Size of float = %d\n", sizeof(float));
	printf("Size of double = %d\n", sizeof(double));
	printf("Size of long double = %d\n", sizeof(long double));
	*/
	/*
	register u8 x1;
	const u8 x = 5;
	u8 y;
	//const u8* ptr1 = &x;
	u8* const ptr2 = &x;
	//ptr2 = &y;
	printf("X before = %d\n", x);
	//*ptr = 10;
	printf("X after = %d\n", x);
	*/
	
	func();
	func();
	func();
	printf("%d", x);
	
	
}