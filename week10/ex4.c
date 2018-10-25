#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <malloc.h>

#define DIR_NAME "../tmp"

typedef struct dirent entry;

int compare(const entry** d1, const entry** d2) {
    return (*d1)->d_ino < (*d2)->d_ino;
}


int main() {

    DIR* d = opendir(DIR_NAME);

    struct dirent** name_list;
    int num = scandir(DIR_NAME, &name_list, NULL, compare);

    if (num == -1) {
        perror("Error during directory scan!");
    }

    __ino_t last_inode = 0;
    while (num--) {

        struct stat s;
        char* fname = malloc(sizeof(char) * (strlen(DIR_NAME) + strlen(name_list[num]->d_name)));
        sprintf(fname, DIR_NAME"/%s", name_list[num]->d_name);
        if(stat(fname, &s) == -1)
            perror("Error during stat!");

        if(S_ISDIR(s.st_mode) || s.st_nlink < 2) continue;

        if(last_inode != name_list[num]->d_ino) {
            last_inode = name_list[num]->d_ino;
            printf("\nSame inum: ");
        }
        printf("%s ", name_list[num]->d_name);
    }

    return 0;
}