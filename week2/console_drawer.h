#ifndef _CONSOLE_DRAWER_H_
#define _CONSOLE_DRAWER_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "reverse.h"


void draw_full_filled_row(unsigned length) {
	char* row = malloc((length + 1) * sizeof(char));
	for(unsigned i = 0; i < length; i++) {
		row[i] = '*';
	}
	row[length] = '\0';
	printf("%s\n", row);
	free(row);
}



void draw_left_filled_row(unsigned level, unsigned length) {
	char* row = malloc((length + 1) * sizeof(char));
	for(unsigned i = 0; i < length; i++) {
		row[i] = (i < level) ? '*' : ' ';
	}
	row[length] = '\0';
	printf("%s\n", row);
	free(row);
}

/* Length 5, level 0: "  *  "
 * 			 level 1: " *** "
 * and so on...
 */
void draw_middle_filled_row(unsigned level, unsigned length) {
	char* row;
	unsigned half_length = length / 2;

	char* half_row = malloc((half_length + 1) * sizeof(char));
	for(unsigned i = 0; i < half_length; i++) {
		half_row[i] = (i < level) ? '*' : ' ';
	}
	half_row[half_length] = '\0';
	row = malloc((length + 1) * sizeof(char));
	strcpy(row, reverse(half_row));
	row[half_length] = '*';
	strcpy(row + half_length + 1, half_row);
	row[length] = '\0';
	printf("%s\n", row);
	
	free(row);
	free(half_row);
}


#endif