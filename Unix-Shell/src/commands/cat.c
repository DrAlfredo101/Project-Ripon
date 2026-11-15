#include <stdio.h>

void print_file(FILE *filepath) {
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), filepath) != NULL) {
        printf("%s", buffer);
    }
}

int main(int argc, char **args) {
    if (argc == 1) {
        print_file(stdin);
        return 0;
    }

    for (int i = 1; args[i] != NULL; i++) {
        FILE *filepath = fopen(args[i], "r");
        if (filepath == NULL) {
            printf("Failed to read file %s\n", args[i]);
            continue;
        }
        print_file(filepath);
        fclose(filepath);
    }
    return 0;
}