#include <stdio.h>
#define _GNU_SOURCE
#define _USE_GNU
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>


int main() {

    int fd = open("../ex1.txt", O_RDWR);

    if(fd == -1) {
        perror("open");
        return -1;
    }

    struct stat buf;
    fstat(fd, &buf);

    void* data = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(data == (void*)-1) {
        perror("mmap");
        return -1;
    }


    char* s = "This is a nice day";
    ftruncate(fd, strlen(s));
    strcpy(data, s);

    close(fd);

    return 0;
}