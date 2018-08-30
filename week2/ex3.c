#include <stdio.h>
#include "console_drawer.h"




int main(int argc, char** argv) {

	if (argc != 2) {
		printf("Please set the height of the pyramid as a command line parameter!\n");
		return 1;
	}
	
	unsigned n = 0;
	sscanf(argv[1], "%d", &n);

	for(unsigned i = 0; i < n; i++) {
		draw_middle_filled_row(i, 2*n - 1);
	}

	return 0;
}