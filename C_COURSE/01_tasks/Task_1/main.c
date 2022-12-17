#include <stdio.h>
#include "bits_manipulations.h"


int main (void) {
	int num, bit, operation, result;
	while (1) {
		printf("Please enter the operation: ");
		scanf("%d", &operation);
		if ((operation>=0) && (operation<=3)) {
			printf("Please enter the number and the bit position: ");
			scanf("%d %d", &num, &bit);
			if ((bit > 31) || (bit < 0)) {
				printf("Invalid Bit Number");
				continue;
			}
			printf("Input in Decimal: %d\n", num);
			printf("Input in Binary: ");
			printBinary(num);
			
		}
		else if ((operation>=4) && (operation<=9)) {
			printf("Please enter the number: ");
			scanf("%d", &num);
			printf("Input in Decimal: %d\n", num);
			printf("Input in Binary: ");
			printBinary(num);

		}
		else if (operation == 10) {
			break;
		}
		else {
			printf("Invalid Operation\n");
			continue;
		}
		
		
		switch (operation) {
			case 0:
				result = clearBit(num, bit);
				printf("Output in Decimal: %d\n", result);
				printf("Output in Binary: ");
				printBinary(result);
				break;
			case 1:
				result = setBit(num, bit);
				printf("Output in Decimal: %d\n", result);
				printf("Output in Binary: ");
				printBinary(result);
				break;
			case 2:
				result = toggleBit(num, bit);
				printf("Output in Decimal: %d\n", result);
				printf("Output in Binary: ");
				printBinary(result);
				break;
			case 3:
				result = getBit(num, bit);
				printf("Bit is: %d\n", result);
				break;
			case 4:
				result = rotateBits(num);
				printf("Output in Decimal: %d\n", result);
				printf("Output in Binary: ");
				printBinary(result);
				break;
			case 5:
				result = flipBits(num);
				printf("Output in Decimal: %d\n", result);
				printf("Output in Binary: ");
				printBinary(result);
				break;
			case 6:
				result = getNumberOfOnes(num);
				printf("Number of Ones is: %d\n", result);
				break;
			case 7:
				result = getNumberOfConsecOnes(num);
				printf("Number of Consecutive Ones is: %d\n", result);
				break;
			case 8:
				result = getFirstPositionOfOne(num);
				printf("First Position of One is: %d\n", result);
				break;
			case 9:
				result = getLastPositionOfOne(num);
				printf("Last Position of One is: %d\n", result);
				break;
			default:
				break;

		}

	}
}