#include <stdio.h>



int main() {
    FILE* rand = fopen("/dev/random", "r");
    FILE* out = fopen("../ex1.txt", "w");
    if(out == NULL) {
        perror("");
        return 0;
    }

    for(int i = 0; i < 20; i++) {
        int c = getc(rand) % ('z'-'a') + 'a';
        putc(c, out);
    }
    fprintf(out, "\n");

    fclose(out);
    fclose(rand);
    return 0;
}