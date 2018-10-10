#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <sys/resource.h>



int main() {

    char* pp_mem[10][1024];
    for(int i = 0; i < 10; i++) {
        for(int c = 0; c < 1024; c++) {
            pp_mem[i][c] = malloc((size_t)(1024));
            if(!pp_mem[i][c]) {
                perror("...");
            } else {
                memset(pp_mem[i][c], 0, (size_t)(1024));
            }
        }
        struct rusage r;
        getrusage(RUSAGE_SELF, &r);
        printf("%d\n", r.ru_maxrss);
        sleep(1);
    }

    for(int i = 0; i < 10; i++) {
        for (int c = 0; c < 100; c++) {
            free(pp_mem[i][c]);
        }
    }

    return 0;
}