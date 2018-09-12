#include <stdio.h>


void swap(int* first, int* second) 
{
	int temp = *second;
	*second = *first;
	*first = temp;
}


int* bubb_sorting(int numbers[], int length)
{
	for (int i = 0;i < length;i++)
	{
		for (int j = i+1;j < length;j++)
		{
			if(numbers[i] >= numbers[j]) {
				swap(&numbers[i], &numbers[j]);
			}
		}
	}
}


int main() {
	int is[] = {88881, 298, 8884, -5};
	bubb_sorting(is, 4);

	for(size_t i = 1;i < 4;i++) {
		if(is[i-1] > is[i]) {
			printf("Fail\n");;
			return 0;
		}
	}
	printf("Ok\n");

	return 0;
}