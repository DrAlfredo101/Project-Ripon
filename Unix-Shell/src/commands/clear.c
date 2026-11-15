#include <stdio.h>

int main(void) {
    printf("\033[H\033[J"); // escape sequence for clear screen
    return 0;
}