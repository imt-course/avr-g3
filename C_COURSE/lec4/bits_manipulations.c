
#include <stdio.h>
#include "bits_manipulations.h"

/*
**
**
*/
int clearBit (int number, int bit) {
	return (number & ~(1<<bit));
}

int setBit (int number, int bit);
int toggleBit (int number, int bit);
int getBit (int number, int bit);
int rotateBits (int number);
int flipBits (int number);
int getNumberOfOnes (int number);
int getNumberOfConsecOnes (int number);
int getFirstPositionOfOne (int number);
int getLastPositionOfOne (int number);
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
