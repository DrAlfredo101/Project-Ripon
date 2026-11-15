#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        return 0;
    } else {
        printf("pwd Failed");
        return -1;
    }
}