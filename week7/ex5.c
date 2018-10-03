#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>



int main() {
    char **s = calloc(1, sizeof(char*));
    char foo[] = "Hello World";
    *s = foo;
    printf("s is %p\n", s);

    s[0] = foo;
    printf("s[0] is %s\n", s[0]);
    return(0);
}
