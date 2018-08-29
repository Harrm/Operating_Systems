#include <stdio.h>
#include "console_drawer.h"




int main() {

	printf("Please input height: ");

	unsigned n;
	scanf("%d", &n);

	for(unsigned i = 0; i < n; i++) {
		draw_full_filled_row(n);
	}
	puts("\n");
	for(unsigned i = 0; i < n; i++) {
		draw_left_filled_row(i, n);
	}


	return 0;
}