#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef void*(*callback_t)(void*);



void run_thread(const int id) {
    printf("%d\n", id);
    printf("Hello, world!\n");
}



void run_mess(int n) {
    pthread_t thread = 0;
    for(int i = 0; i < n; i++) {
        pthread_create(&thread, NULL, (callback_t)run_thread, i);

    }
    pthread_join(thread, NULL);
    sleep(1);
}



void run_neat_one(int n) {
    pthread_t thread = 0;
    for(int i = 0; i < n; i++) {
        pthread_create(&thread, NULL, (callback_t)run_thread, i);
        pthread_join(thread, NULL);
    }
}



int main() {

    run_mess(100);
    run_neat_one(100);

    return 0;
}
