#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef void*(*callback_t)(void*);

typedef struct { int n1; int n2; } pair_t;


int calc_gcd(int n1, int n2) {
    if (n1 == 0 || n2 == 0) {
        return 0;
    }

    if (n1 == n2) {
        return n1;
    }

    if (n1 > n2) {
        return calc_gcd(n1 - n2, n2);
    } else {
        return calc_gcd(n1, n2 - n1);
    }
}



int calc_lcm(pair_t* arg) {
    int n1 = arg->n1;
    int n2 = arg->n2;

    int gcd = calc_gcd(n1, n2);
    int res = gcd ? (n1 * n2 / gcd) : 0;
    printf("For %d, %d %d is the result\n", n1, n2, res);
    return res;
}





int main(int argc, char** argv) {

    if(argc != 3) {
        printf("Invalid arguments. Should be the name of the file with numbers and the number of threads");
    }

    FILE* f = fopen(argv[1], "r");
    if(!f) {
        perror("Error opening the file\n");
    }

    size_t threads_num = strtoul(argv[2], NULL, 10);

    int n1 = 0, n2 = 0;
    pthread_t threads[threads_num];
    pair_t* args = calloc(threads_num, sizeof(pair_t));
    size_t curr_thread = 0;
    while(fscanf(f, "%d %d", &n1, &n2) != EOF) {
        pair_t* arg_set = &args[curr_thread];
        arg_set->n1 = n1;
        arg_set->n2 = n2;
        pthread_create(&threads[curr_thread], NULL, (callback_t)calc_lcm, arg_set);
        curr_thread++;
        printf("Spawn %d, %d %d\n", curr_thread, arg_set->n1, arg_set->n2);
        /*if(curr_thread == threads_num) {
            int results[curr_thread];
            wait_for(threads, curr_thread, results);
            for(int i = 0; i < threads_num; i++) {
                printf("LCM for %d %d is %d\n", i, args[i].n1, args[i].n2, results[i]);
            }
            curr_thread = 0;
        }*/
    }
    if(curr_thread != 0) {
        int results[curr_thread];
        for(int i = 0; i < curr_thread; i++) {
            printf("%d\n", i);
            int* ret = calloc(1, 4);

            pthread_join(threads[i], (void**)(&ret));
            printf("LCM for %d %d is %d\n", args[i].n1, args[i].n2, *ret);
            free(ret);
        }
    }
    free(args);

    return 0;
}
