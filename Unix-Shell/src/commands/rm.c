#include <stdio.h>

int main(int argc, char **args) {
    (void)argc;
    if (args[1] == NULL) {
        printf("No Filename Passed\n");
        return -1;
    }
    for (int i = 1; args[i] != NULL ;i++) {
        if (remove(args[i]) != 0) {
            printf("File \"%s\" Could Not Be Removed\n", args[i]);
        }
    }
    return 0;
}
