/*#include <string.h>
#include <stdio.h>
#include <zconf.h>



int main() {

    const char* s = "Hello";
    for(int i = 0; i < strlen(s); i++) {
        fprintf(stderr, "Tick\n");
        printf("%c", s[i]);
        sleep(1);
    }
    sleep(5);
    printf("\n"); // just in case
    // and print Hello
}*/
#include <stdio.h>
#include <unistd.h>
int main(void) {
    printf("Hello\n");
    fork();
    printf("\n");
    return 0;
}