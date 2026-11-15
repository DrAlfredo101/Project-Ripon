#include <stdio.h>
#include <dirent.h>

int main(void) {

    DIR *directory = opendir(".");
    if (directory == NULL) {
        printf("Failed to Open Directory");
        return -1;
    }

    struct dirent *entry;
    while((entry = readdir(directory))) {

        if (entry->d_name[0] != '.') { // does not return current or parent directories, or hidden directories and files
            printf("%s\n", entry->d_name);
        }
    }

    closedir(directory);
    return 0;
}