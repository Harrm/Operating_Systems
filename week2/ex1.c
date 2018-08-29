#include <limits.h>
#include <float.h>
#include <stdio.h>

int main() {

	int i = INT_MAX;
	float f = FLT_MAX;
	double d = DBL_MAX;

	printf("Int max: %d, size: %d; Float max: %f, size: %d; Double max: %f, size: %d\n",
		   i, sizeof i, f, sizeof f, d, sizeof d);

	return 0;
}