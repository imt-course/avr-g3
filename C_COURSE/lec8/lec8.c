#include <stdio.h>
#include "Types.h"

struct Student {
	u8 id;
	u16 math;
	u16 english;
};

typedef struct {
	u16 salary;
	u16 bonus;
	u16 deductions;
	u16 net;
}Employee;

typedef struct {
	u16 sum;
	u16 diff;
	u16 mul;
	u16 mod;
	f32 div;
} CalcResult ;

typedef struct {
	s32 x;
	s32 y;
} Complex;

typedef struct {
	u8 a;  //1
	u8 d;  //1
	u8 h;  //1
	u16 b; //2
	u16 f; //2
	u32 c; //4
	u32 e; //4
	u32 g; //4
} MyStruct;//19

typedef union {
	u8 x;
	u16 y;
	u32 m;
} MyUnion;

typedef struct {
	s8 x : 3;
	u8 y : 2;
	u8 m : 1;
	u8 n : 2;
} BitField;

typedef struct {
	u8 B0 : 1;
	u8 B1 : 1;
	u8 B2 : 1;
	u8 B3 : 1;
	u8 B4 : 1;
	u8 B5 : 1;
	u8 B6 : 1;
	u8 B7 : 1;
} Btye;

typedef union {
	Btye bit;
	u8 byte;
} Register;

Complex addComplex(Complex n1, Complex n2);
Complex addComplex_(const Complex *n1_ref, const Complex *n2_ref);
CalcResult calculate (u16 x, u16 y);


int main (void) {
	/*
	struct Student ahmed = {1,220};
	struct Student ali;
	ali.math = 200;
	ali.id = 2;
	ali.english = 250;
	printf("ahmed.id = %d\n", ahmed.id);
	printf("ahmed.math = %d\n", ahmed.math);
	printf("ahmed.english = %d\n", ahmed.english);
	printf("ali.id = %d\n", ali.id);
	printf("ali.math = %d\n", ali.math);
	printf("ali.english = %d\n", ali.english);
	*/
	
	/*Employee ahmed, ali, waleed;
	u16 total_pay;
	
	printf("Enter ahmed salary: ");
	scanf("%d", &ahmed.salary);
	printf("Enter ahmed bonus: ");
	scanf("%d", &ahmed.bonus);
	printf("Enter ahmed deductions: ");
	scanf("%d", &ahmed.deductions);
	ahmed.net = ahmed.salary + ahmed.bonus - ahmed.deductions;

	printf("Enter ali salary: ");
	scanf("%d", &ali.salary);
	printf("Enter ali bonus: ");
	scanf("%d", &ali.bonus);
	printf("Enter ali deductions: ");
	scanf("%d", &ali.deductions);
	ali.net = ali.salary + ali.bonus - ali.deductions;

	printf("Enter waleed salary: ");
	scanf("%d", &waleed.salary);
	printf("Enter waleed bonus: ");
	scanf("%d", &waleed.bonus);
	printf("Enter waleed deductions: ");
	scanf("%d", &waleed.deductions);
	waleed.net = waleed.salary + waleed.bonus - waleed.deductions;

	total_pay = ahmed.net + ali.net + waleed.net;
	printf("Total = %d", total_pay);*/
	
	/*
	Employee employees[10];
	u8 n, i;
	u16 total_pay = 0;
	
	printf("Please enter number of employees: ");
	scanf("%d", &n);
	
	for (i=0; i<n; i++) {
		printf("Enter employee %d salary: ", i+1);
		scanf("%d", &employees[i].salary);
		printf("Enter employee %d bonus: ", i+1);
		scanf("%d", &employees[i].bonus);
		printf("Enter employee %d deductions: ", i+1);
		scanf("%d", &employees[i].deductions);
		employees[i].net = employees[i].salary + employees[i].bonus - employees[i].deductions;
		total_pay += employees[i].net;
	}
	
	printf("Total = %d", total_pay);
	*/
	
	/*
	CalcResult output;
	
	output = calculate(5,2);
	
	printf("sum = %d\n", output.sum);
	printf("diff = %d\n", output.diff);
	printf("mul = %d\n", output.mul);
	printf("mod = %d\n", output.mod);
	printf("div = %.1f\n", output.div);
	*/
	
	/*
	Complex n1, n2, result;
	printf("Enter number 1: ");
	scanf("%d %di", &n1.x, &n1.y);
	printf("Enter number 2: ");
	scanf("%d %di", &n2.x, &n2.y);
	//result = addComplex(n1, n2);
	result = addComplex_(&n1, &n2);
	printf("Sum = %d%+di", result.x, result.y);
	*/
	/*
	BitField a;
	a.x = 5;
	a.y = 7;
	a.m = 1;
	printf("x = %d\n", a.x);
	printf("y = %d\n", a.y);
	printf("m = %d\n", a.m);
	*/
	MyUnion a;
	a.y = 0;
	a.m = 0;
	a.x = 10;
	printf("x = %d\n", a.x);
	printf("y = %d\n", a.y);
	printf("m = %d\n", a.m);
	a.y = 5;
	printf("x = %d\n", a.x);
	printf("y = %d\n", a.y);
	printf("m = %d\n", a.m);
	a.m = 0x01234567;
	printf("x = %x\n", a.x);
	printf("y = %x\n", a.y);
	printf("m = %x\n", a.m);

	Register reg;
	reg.byte = 0;
	reg.bit.B5 = 1;
	reg.bit.B7 = 1;
	printf("%d", reg.byte);
	
	reg.byte = 17;

}

CalcResult calculate (u16 x, u16 y) {
	CalcResult res;
	res.sum = x+y;
	res.diff = x-y;
	res.mul = x*y;
	res.mod = x%y;
	res.div = (f32)x/y;
	return res;
}

Complex addComplex(Complex n1, Complex n2) {
	Complex result;
	result.x = n1.x + n2.x;
	result.y = n1.y + n2.y;
	return result;
}


Complex addComplex_(const Complex *n1_ref, const Complex *n2_ref) {
	Complex result;
	//result.x = (*n1).x + (*n2).x;
	result.x = n1_ref->x + n2_ref->x;
	//result.y = (*n1).y + (*n2).y;
	result.y = n1_ref->y + n2_ref->y;

	return result;
}
