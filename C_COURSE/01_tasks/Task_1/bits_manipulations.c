
#include <stdio.h>
#include "bits_manipulations.h"

/*
** Function Name	: clearBit
** Parameters In	: - number: number to clear bit in.
** 				      - bit: bit order to be cleared.
** Parameters Out	: None.
** Return			: Number after clearing the bit.
** Description		: Clears specific bit in number.
*/
int clearBit (int number, int bit) {
	return (number & ~(1<<bit));
}

int setBit (int number, int bit) {
	return (number | (1<<bit));
}

int toggleBit (int number, int bit) {
	return (number ^ (1<<bit));
}

int getBit (int number, int bit) {
	return ((number >> bit) & 1);
}

int rotateBits (int number) {
	int i, res = 0;
	for (i=31; i>=0; i--) {
		res |= ((number&1)<<i);
		number >>= 1;
	}
	return res;
}

int flipBits (int number) {
	return (~number);
}

int getNumberOfOnes (int number) {
	int i, counter = 0;
	for (i=0; i<32; i++) {
		if ((number&1) == 1) {
			counter++;
		}
		number >>= 1;
	}
	return counter;
}

int getNumberOfConsecOnes (int number) {
	int count = 0, max = 0;
	while (number >= 0) {
		if ((number&1) == 1) {
			count++;
		}
		else {
			if (count > max) {
				max = count;
			}
			if (number == 0) {
				break;
			}
			count = 0;
		}
		number >>= 1;
	}
	return max;
}

int getFirstPositionOfOne (int number) {
	int i;
	for (i=0; i<32; i++) {
		if (number&1 == 1) {
			break;
		}
		number >>= 1;
	}
	return i;

}

int getLastPositionOfOne (int number) {
	int i=0, index = 32;
	while (number > 0) {
		if (number&1 == 1) {
			index = i;
		}
		number >>= 1;
		i++;
	}
	return index;

}

/*
** Function Name	: printBinary
** Parameters In	: - number: number to be printed.
** Parameters Out	: None.
** Return			: None.
** Description		: Prints the number in binary format.
*/
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