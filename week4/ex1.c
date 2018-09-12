#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// the child's pid's different from parent's, usually greater by one

int main() {

    int n = 0;

    if(fork() == 0) {
        printf("Hello from child, %d - %d\n", (int)getpid(), n);
    } else {
        printf("Hello from parent, %d - %d\n", (int)getpid(), n);
    }


    return 0;
}