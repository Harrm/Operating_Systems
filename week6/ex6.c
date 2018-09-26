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

void kill_handler() {
    printf("!!!Killed!!!\n");
}

int main() {
    int my_pipe[2];
    pipe(my_pipe); // first -- reading, second -- writing

    printf("Root: Creating first child.\n");
    int first_child_id = fork();

    if(first_child_id != 0) {

        printf("Root: Creating second child.\n");
        int second_child_id = fork();

        if(second_child_id != 0) {
            close(my_pipe[0]);

            char* s = calloc(32, sizeof(char));
            memset(s, 0, 32 * sizeof(char));

            sprintf(s, "%d", second_child_id);
            write(my_pipe[1], s, 32);
            printf("Root: 2nd's ID: %s\n", s);

            waitpid(second_child_id, NULL, 0);
            printf("Root: Second child stopped.\n");


        } else {
            printf("2nd child: Created.\n");
            struct sigaction s;
            s.sa_handler = kill_handler;
            sigaction(SIGKILL, &s, NULL);
            while(1) {
                sleep(1);
                printf("2nd child: Alive.\n");
            }
        }

    } else {
        printf("1st child: Created.\n");
        close(my_pipe[1]);
        char* s2 = calloc(32, sizeof(char));
        memset(s2, 0, 32 * sizeof(char));
        read(my_pipe[0], s2, 32);
        printf("1st child: %s\n", s2);
        int second_child_id = 0;
        sscanf(s2, "%d", &second_child_id);
        printf("1st child: Received 2nd's ID: %d.\n", second_child_id);
        sleep(2);
        printf("1st child: Awaken\n");
        kill(second_child_id, SIGKILL);
        printf("1st child: Stopped 2nd.\n");
    }

    return 0;
}
