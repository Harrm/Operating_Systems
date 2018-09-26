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



int main() {

    int child_id = fork();
    if(child_id == 0) {
        while(1) {
            printf("I'm alive!\n");
            sleep(1);
        }
    } else {
        sleep(5);
        kill(child_id, SIGTERM);
    }

    return 0;
}
