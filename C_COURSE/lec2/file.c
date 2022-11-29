#include <stdio.h>

int main (void) {
	/********************** LAB 1 **********************/
	/*
	int x,y;
	printf("Please enter first number: ");
	scanf("%d", &x);
	printf("Please enter second number: ");
	scanf("%d", &y);
	printf("%d + %d = %d\n", x, y, x+y);
	printf("%d - %d = %d\n", x, y, x-y);
	printf("%d * %d = %d\n", x, y, x*y);
	printf("%d / %d = %f\n", x, y, (float)x/y);
	printf("%d %% %d = %d\n", x, y, x%y);
	*/
	
	/********************** LAB 2 **********************/
	/*
	int x = 10;
	int y = x++;
	printf("x = %d\n", x);
	printf("y = %d\n", y);
	y = ++x;
	printf("x = %d\n", x);
	printf("y = %d\n", y);	
	*/

	/********************** LAB 3 **********************/
	/*
	char x = 25;
	char y = 85;
	printf("OR %d\n", x|y);
	printf("AND %d\n", x&y);
	printf("XOR %d\n", x^y);
	printf("~X %d\n", ~x);
	printf("~Y %d\n", ~y);
	x+= 10;
	printf("x %d\n", x);
	*/
	
	/********************** LAB 4 **********************/
	/*
	int x,y;
	printf("Please enter first number: ");
	scanf("%d", &x);
	printf("Please enter second number: ");
	scanf("%d", &y);
	printf("Greater: %d", x>=y);
	*/

	/********************** LAB 5 **********************/
	/*
	int grade;
	printf("Please enter your grade: ");
	scanf("%d", &grade);
	if ((grade>100) || (grade<0)) {
		printf("INVALID INPUT");
	}
	else if (grade >= 85) {
		printf("EXCELLENT")
	}
	else if (grade >= 75){
		printf("V.G");
	}
	else if (grade >= 65){
		printf("G");
	}
	else if (grade >= 75){
		printf("V.G");
	}
	else if (grade >= 50){
		printf("PASS");
	}
	else {
		printf("FAIL");
	}
	*/
	
	/********************** LAB 6 **********************/
	/*
	int num;
	printf("Please enter number: ");
	scanf("%d", &num);
	if ((num%2) == 0) {
		printf("EVEN");
	}
	else {
		printf("ODD")
	}
	*/
	
	/********************** LAB 7 **********************/
	/*
	int id;
	printf("Please enter id: ");
	scanf("%d", &id);
	switch (id) {
		case 1234:
			printf("Welcome Ahmed");
			break;
		case 5678:
			printf("Welcome Youssef");
			break;
		case 1145:
			printf("Welcome Mina");
			break;
		default:
			printf("INVALID ID");
			break;
	}
	*/
	/********************** LAB 7 **********************/
	int d1,m1,y1;
	int d2,m2,y2;
	printf("Please enter first date: ");
	scanf("%d/%d/%d", &d1, &m1, &y1);
	printf("Please enter second date: ");
	scanf("%d/%d/%d", &d2, &m2, &y2);
	
	if (y1>y2) {
		printf("Second date is earlier");
	}
	else if (y1<y2) {
		printf("First date is earlier");
	}
	
	else {
		
		if (m1>m2) {
			printf("Second date is earlier");
		}
		else if (m1<m2) {
			printf("First date is earlier");
		}
		
		else {
			
			if (d1>d2) {
				printf("Second date is earlier");
			}
			else if (d1<d2) {
				printf("First date is earlier");
			}
			
			else {
				printf("Two dates are the same");
			}
		}
	}
}
