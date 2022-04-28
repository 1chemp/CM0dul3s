#include <stdio.h>
#include <math.h>

int sqr(int* param) {
	*param = *param * *param;
	printf("Result of power 2: %d\n", *param);
	return *param;
}
