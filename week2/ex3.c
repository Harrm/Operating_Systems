#include <stdio.h>
#include "console_drawer.h"




int main() {

	printf("Please input height: ");
	
	unsigned n;
	scanf("%d", &n);

	for(unsigned i = 0; i < n; i++) {
		draw_middle_filled_row(i, 2*n - 1);
	}

	return 0;
}