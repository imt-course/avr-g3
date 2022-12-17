#include <stdio.h>
#include "Types.h"

static u8 x = 5;

void func (void) {
	static u8 counter;
	counter++;
	printf("Called %d\n", counter);
}