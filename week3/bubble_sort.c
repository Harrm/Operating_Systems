#include <stdio.h>



void swap(int* i1, int* i2) {
	int t = *i1;
	*i1 = *i2;
	*i2 = t;
}



int* bubble_sort(int array[], size_t size) {
	for (size_t i = 0; i < size; i++) {
		for (size_t j = i+1; j < size; j++) {
			if(array[i] > array[j]) {
				swap(&array[i], &array[j]);
			}
		}
	}
}



int is_ascending(int array[], size_t size) {
	for(size_t i = 1; i < size; i++) {
		if(array[i-1] > array[i]) {
			return 0;
		}
	}
	return 1;
}



void test_case(int array[], size_t size) {
	bubble_sort(array, size);
	if(is_ascending(array, size)) {
		printf("Success\n");
	} else {
		printf("Failure: {");
		for(size_t i = 0; i < size; i++) {
			printf("%d ", array[i]);
		}
		printf("}\n");
 	}
}


int main() {
	test_case((int[]){1, 2, 3, 4, 5}, 5);
	test_case((int[]){3, 200, 3, -4, 5}, 5);
	test_case((int[]){0, 288, 0, 0, 5}, 5);
	test_case((int[]){88881, 298, 893, 8884, -5}, 5);

	return 0;
}