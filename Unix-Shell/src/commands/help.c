#include <stdio.h>

int main(void) {

    printf("|----------------------------|\n\n");

    printf("This is RSH by Alfie Howard, written as part of Project-Ripon (Temporary Name)\n");
    printf("To use it, type the command or program you wish to run, followed by any additional arguments.\n");
    printf("The following, as well as possibly others, are built in. This command will be updated with new commands, whenever I remember\n\n");
    printf("There is currently no support for :\n1) using flags on the commands\n2) using multiple operators in one command (< >> >)\n");
    printf("\n|----------------------------|\n\n");
    
    printf("COMMANDS:\n\n");
    printf("cd - Change directory, attach the directory to change to as an argument\n");
    printf("exit - Exit the shell\n");
    printf("help - Reach this help message\n");
    printf("pwd - Print current directory\n");
    printf("clear - Clear the terminal\n");
    printf("echo - Print the arguments after the command to the terminal\n");
    printf("rm - Deletes the specified files. Currently no support for removing directories. Files should be separated by spaces (" ")\n");
    printf("ls - Outputs the files and sub-drectories in the current directory, excluding hidden files\n");
    printf("cat - Reads the contents of the file passed as an argument and outputs them to the terminal");

    printf("\n|----------------------------|\n\n");

    printf("OPERATORS\n\n");
    printf("> - Redirect the command output into the file following the operator, overwriting what is in that file\n");
    printf(">> - Redirect the command output into the file following the operator, appending to the end of the file\n");
    
    printf("\n");
    return 0;
}