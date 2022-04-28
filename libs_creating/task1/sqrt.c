#include <stdio.h>
#include <math.h>

int msqrt(int *param) {
	
	*param = sqrt((double)*param);

	printf("Result of sqrt: %d\n", *param);
	return *param;
}
