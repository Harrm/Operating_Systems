#include <stdio.h>

void swap(int* x, int* y) {
	if(*x != *y) {
		*x ^= *y;
		*y ^= *x;
		*x ^= *y;
	}
}

int main() {

	int x1 = 0, x2 = 0;
	printf("Please input two integers: ");
	scanf("%d %d", &x1, &x2);

	swap(&x1, &x2);
	printf("Swapped: %d %d\n", x1, x2);

	return 0;
}