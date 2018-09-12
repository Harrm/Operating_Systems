#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include<sys/wait.h>


/*
 * s -- the line to parse
 * args -- array of strings where the arguments will be put. Each argument is allocated in dynamic memory
 * args_num -- the maximum number of arguments, should be no more than args size
 */

void parse_arguments(const char* s, char** args, size_t args_num) {
    int curr_arg = 0;
    size_t curr_pos = 0;
    char arg[256];
    for(int i = 0; s[i] != '\0' && curr_arg < args_num; i++) {
        if(!isblank(s[i]) && !isspace(s[i])) {
            arg[curr_pos] = s[i];
            curr_pos++;
        } else {
            if(curr_pos != 0) {
                arg[curr_pos] = '\0';

                args[curr_arg] = calloc(curr_pos + 1, sizeof(char));
                strcpy(args[curr_arg], arg);
                curr_arg++;
            }
            curr_pos = 0;
        }
    }
    args[curr_arg] = NULL;
}

void free_arguments(char** args, size_t args_num) {
    for(int i = 0; i < args_num && args[i] != NULL; i++) {
        free(args[i]);
    }
}



int main(int argc, char** argv) {

    while(1) {
        printf(">> ");

        char* buf = calloc(256, sizeof(char));
        memset(buf, 0, 256 * sizeof(char));
        size_t chars_read = 0;

        getline(&buf, &chars_read, stdin);
        if(strcmp(buf, "exit") == 0) break;

        char program_name[256] = "";
        sscanf(buf, "%s", program_name);
        if(strcmp(program_name, "exit") == 0) {
            continue;
        }

        char* args[16];
        parse_arguments(buf, args, 16);

        int my_pipe[2];
        pipe(my_pipe); // first -- reading, second -- writing


        if(fork() == 0) {
            close(my_pipe[0]);
            dup2(my_pipe[1], 1);
            dup2(my_pipe[1], 2);
            printf("args:");
            for(int i = 0; args[i] != NULL; i++) {
                printf("%s\n", args[i]);
            }
            if(execve(program_name, args, __environ) == -1) {
                printf("\nEXECVE failed: %s\n", strerror(errno));
                return -1;
            }
        } else {
            close(my_pipe[1]);
            char abc[256];
            wait(NULL);
            ssize_t rn = 0;
            while((rn = read(my_pipe[0], abc, 256)) > 0) {
                abc[rn] = '\0';
                printf("OUTPUT: '%s'\n", abc);
            }
        }
    }

    return 0;
}