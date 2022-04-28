#include <stdio.h>
// Операции возведения в квадрат и извлечения корня.


extern void sqr(int* param);


extern void msqrt(int* param);


int main(int argc, char** argv) {

	int number;
	printf("Hello, give me integer number: "); scanf("%d",&number); getchar();

	sqr(&number);
	msqrt(&number);

	return 0;
}
