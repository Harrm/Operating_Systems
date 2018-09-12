#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// the result grows exponentially, as every forked process forks more processes n times

int main(int argc, char** argv) {

    assert(argc == 2);

    unsigned  long n = strtoul(argv[1], &argv[1] + strlen(argv[1]), 10);

    for(unsigned long i = 0; i < n; i++) {
        fork();
        sleep(5);
    }


    return 0;
}