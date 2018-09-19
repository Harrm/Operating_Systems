#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void*(*callback_t)(void*);
typedef bool condition_t;

typedef struct shared_buffer_t {
    int* data;
    size_t size;
    size_t max_size;
    condition_t full, empty;
} shared_buffer_t;



void sleep_until(condition_t* cond) {
    *cond = false;
    while (!*cond) {
        usleep(10);
    }
}



void wakeup(condition_t* cond) {
    *cond = true;
}



void start_producer(shared_buffer_t* buffer) {
    for(int i = 0; i < 100; i++) {
        if (buffer->size == buffer->max_size) {
            wakeup(&buffer->full);
            sleep_until(&buffer->empty);
        }
        buffer->data[++buffer->size] = 100+i;
    }
    wakeup(&buffer->full);
}



void start_consumer(shared_buffer_t* buffer) {
    int read[100];
    for(int i = 0; i < 100; i++) {
        if (buffer->size == 0) {
            wakeup(&buffer->empty);
            sleep_until(&buffer->full);
        }
        read[i] = buffer->data[--buffer->size];
    }
    for(int i = 0; i < 100; i++) {
        printf("%d ", read[i]);
    }
}



int main() {
    shared_buffer_t buffer;
    buffer.data = calloc(10, sizeof(int));
    buffer.max_size = 10;
    buffer.size = 0;

    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, (callback_t)start_producer, &buffer);
    pthread_create(&consumer_thread, NULL, (callback_t)start_consumer, &buffer);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}