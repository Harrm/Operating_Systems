#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>



void* crealloc(void* ptr, size_t new_elem_num, size_t elem_size) {
    void* new_ptr = calloc(new_elem_num, elem_size);
    if(ptr != NULL) {
        memcpy(new_ptr, ptr, new_elem_num * elem_size);
        free(ptr);
    }

    return new_ptr;
}



int main() {

    int* a = calloc(10, sizeof(int));
    for(int i = 0; i < 10; i++) {
        a[i] = i;
    }

    a = crealloc(a, 15, sizeof(int));
    for(int i = 0; i < 15; i++) {
        printf("%d ", a[i]);
    }
    putchar('\n');

    a = crealloc(a, 3, sizeof(int));
    for(int i = 0; i < 3; i++) {
        printf("%d ", a[i]);
    }
    putchar('\n');

    return 0;
}
