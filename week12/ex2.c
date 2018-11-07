#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


ssize_t read_to(void** pdata) {
    *pdata = malloc(256);
    ssize_t data_size = 0;
    size_t data_capacity = 256;
    char buf[256];
    ssize_t num_read = 0;
    while((num_read = read(STDIN_FILENO, buf, 256)) != 0) {
        if (num_read == -1) {
            return -1;
        }
        memcpy(*pdata + data_size, buf, num_read);
        data_size += num_read;
        if(data_size > data_capacity) {
            data_capacity *= 2;
            void* new_data = malloc(data_capacity);
            memcpy(new_data, *pdata, data_capacity / 2);
            free(*pdata);
            *pdata = new_data;
        }
    }
    return data_size;
}



size_t min(size_t i, size_t c) {
    return (i < c) ? i : c;
}



void output_to(int fd, void* data, size_t size) {
    size_t written = 0;
    while(written < size) {
        size_t block_size = min(256, size - written);
        write(fd, data, block_size);
        written += block_size;
    }
}



int main(int argc, char** argv) {
    void* data = NULL;
    ssize_t data_size = read_to(&data);
    if (data_size == -1) {
        perror("Error reading data:\n");
    }

    output_to(STDOUT_FILENO, data, (size_t) data_size);
    for (int i = 1; i < argc; i++) {
        int f = -1;
        if (argv[i][0] != '-') {
            f = open(argv[i], O_RDWR | O_CREAT, S_IRWXU);

        } else if (argv[i][1] == 'a') {
            i++;
            f = open(argv[i], O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
            if (i >= argc) {
                fprintf(stderr, "A filename is required after -a\n");
            }

        } else {
            fprintf(stderr, "Invalid argument: %s\n", argv[i]);
        }

        if(f != -1) {
            output_to(f, data, (size_t) data_size);

        } else {
            perror("Error opening file:\n");
        }
    }

    return 0;
}