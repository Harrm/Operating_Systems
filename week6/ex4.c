//
// Created by xappm on 26.09.18.
//

#include <signal.h>
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

int toExit = 0;

void sigkill_handler() {
    printf("Kill!\n");
    toExit = 1;
}


void sigstop_handler() {
    printf("Stop!\n");
    toExit = 1;
}

void sigusr1_handler() {
    printf("USR1!!!11\n");
}

int main() {

    struct sigaction s1;
    s1.sa_handler = sigkill_handler;
    sigaction(SIGKILL, &s1, NULL);


    struct sigaction s2;
    s2.sa_handler = sigstop_handler;
    sigaction(SIGSTOP, &s2, NULL);


    struct sigaction s3;
    s3.sa_handler = sigusr1_handler;
    sigaction(SIGUSR1, &s3, NULL);

    while(!toExit) {
        usleep(100);
    }
    return 0;
}
