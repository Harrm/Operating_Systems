#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reverse.h"



int main() {
	char s[256];

	printf("Please input a string (no more than 256 characters long): ");

	if(fgets(s, 256, stdin) != NULL) {
		s[strlen(s)-1] = '\0';
		printf("%s", reverse(s));

	} else {
		if(ferror(stdin) != 0) {
			printf("An error has occured during input.\n");
		}
	}
	

	return 0;
}