#include <stdio.h>
#include "Types.h"
#include "Macros.h"

#define PI 3.14
#define SATURDAY 0
#define SUNDAY 1


#define ADD(X,Y) X+Y
typedef enum {
	SAT = 5,
	SUN,
	MON = 10,
	TUE,
	WED,
	THU = 0,
	FRI,
} Day;

typedef enum {
	PORTA,
	PORTB,
	PORTC,
	PORTD
} PortType;

#define PRINT_NAME() do { \
	printf("Ahmed\n"); \
	printf("Hassan\n"); \
} while (0)

typedef int* ptr_to_int1;
#define ptr_to_int2 int*

void getArraySize(int *arr) {
	printf("in function size = %d\n", sizeof(arr));
}

int main (void) {
	int arr[5] = {1,2,3,4,5};
	printf("size = %d\n", sizeof(arr)/sizeof(arr[0]));
	getArraySize(arr);
	return 0;
	printf("Hello");
	/*
	ptr_to_int1 a,b,c;
	ptr_to_int2 x,y,z;
	printf("%d\n", sizeof(a));
	printf("%d\n", sizeof(b));
	printf("%d\n", sizeof(c));
	printf("%d\n", sizeof(x));
	printf("%d\n", sizeof(y));
	printf("%d\n", sizeof(z));
	*/
	
	/*
	u8 x = 5;
	if (x == 5)
		PRINT_NAME();
	else
		printf("Invalid");
	*/
	
	
	/*
	u8 x = 10;
	u8 bit;
	bit = GET_BIT(x,2);
	printf("GET_BIT = %d\n", bit);
	CLR_BIT(x,2);
	printf("CLR_BIT = %d\n", x);
	SET_BIT(x,2);
	printf("SET_BIT = %d\n", x);
	TOG_BIT(x,2);
	printf("TOG_BIT = %d\n", x);
	*/
	
	
	
	
	
	/*BooleanType flag = FALSE;
	PortType port;
	Day day = TUE;
	u8 x = TUE;
	printf("%d\n", day);
	printf("size = %d\n", sizeof(day));
	x = ADD(3,4);
	PRINT();
	CLR_BIT(x,0);*/
	
	/*
	if (x == 10) {
		printf("x = 10\n");
	}
	else {
		printf("x != 10\n");
	}
	printf("Common code\n");
	#if defined BM
	printf("BM Code\n");
	#elif defined BTLD
	printf("BTLD Code\n");
	#endif

	
	printf("Common code\n");
	printf("Common code\n");
	*/
}