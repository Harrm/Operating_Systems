
#include <malloc.h>



int main() {

    int n = 0;
    scanf("%d", &n);

    int* arr = calloc(n, sizeof(int));
    for(int i = 0; i < n; i++) {
        arr[i] = i;
        printf("%d ", arr[i]);
    }
    free(arr);

    return 0;
}