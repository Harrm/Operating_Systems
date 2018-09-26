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

void handler() {
    printf("Aaaaaa!\n");
    toExit = 1;
}



int main() {

    struct sigaction s;
    s.sa_handler = handler;
    sigaction(SIGINT, &s, NULL);
    while(!toExit) {
        usleep(100);
    }
    return 0;
}
