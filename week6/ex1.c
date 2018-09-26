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

    const char* s1 = "Hello, world!\n";
    char* s2 = calloc(strlen(s1), sizeof(char));

    write(my_pipe[1], s1, strlen(s1));
    read(my_pipe[0], s2, strlen(s1));

    printf("%s %s", s1, s2);

    close(my_pipe);
    close(my_pipe+1);

    return 0;
}
