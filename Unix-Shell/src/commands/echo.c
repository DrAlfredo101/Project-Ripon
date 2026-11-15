#include <stdio.h>

int main(int argc, char **args) {
    (void)argc;
    
    for (int i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");

    return 0;
}