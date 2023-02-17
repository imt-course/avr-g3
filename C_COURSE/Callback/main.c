#include <stdio.h>

void print (int x) {
    printf("X = %d\n", x);
}

int main (void) {
    void (*ptr) (int);
    ptr = print;
    printf("Address of function print() = %p\n", print);
    print(5);
    ptr(3);
    printf("Done");

}