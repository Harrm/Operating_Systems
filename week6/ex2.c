//
// Created by xappm on 26.09.18.
//
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <sys/wait.h>



int main() {
    int my_pipe[2];
    pipe(my_pipe); // first -- reading, second -- writing


    if(fork() == 0) {
        close(my_pipe[1]);
        char* s2 = calloc(32, sizeof(char));
        memset(s2, 0, 32 * sizeof(char));
        read(my_pipe[0], s2, 32);
        printf("Child: %s", s2);

    } else {
        close(my_pipe[0]);
        const char* s1 = "Hello, world!\n";
        write(my_pipe[1], s1, strlen(s1));
        printf("%s", s1);
    }

    return 0;
}
