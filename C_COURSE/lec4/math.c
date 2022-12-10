#include "math.h"

int power (int num, int exp) {
	int result = 1;
	int i;
	for (i=0; i<exp; i++) {
		result *= num;
	}
	return result;
}

int add (int x, int y) {
	int sum = x+y;
	return sum;
}
