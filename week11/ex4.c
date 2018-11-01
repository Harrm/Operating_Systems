#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>


int main() {

    int fd = open("../ex1.txt", O_RDONLY);

    if(fd == -1) {
        perror("open");
        return -1;
    }

    struct stat buf;
    fstat(fd, &buf);

    void* data = mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if(data == (void*)-1) {
        perror("mmap");
        return -1;
    }

    int fnewd = open("../ex1.memcpy.txt", O_RDWR | O_CREAT, S_IRWXU);
    ftruncate(fnewd, buf.st_size);

    void* data_new = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fnewd, 0);
    if(data_new == (void*)-1) {
        perror("mmap");
        return -1;
    }

    memcpy(data_new, data, buf.st_size);

    msync(data_new, buf.st_size, MAP_SHARED);

    return 0;
}