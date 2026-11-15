#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <libgen.h>
#include <fcntl.h>
#include <signal.h> 


// Global variables
char *GLOBAL_BINARY_PATH;

// operator tokens (e.g |, >> etc)
char *operator_tokens[] = {
    ">",
    ">>",
    "<" // kind of useless at present due to the commands i have implemented so far, but I only realised that after writing it, so it stays.
    //"|" implement later
};
// functions for operators go here

int output_write(char *filename) {
    int file_descriptor = open(filename,O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_descriptor == -1) {
        printf("Failed To Open File To Write\n");
        exit(EXIT_FAILURE);
    }
    dup2(file_descriptor, 1); 
    close(file_descriptor);
    return 0;
}

int output_append(char *filename) {

    int file_descriptor = open(filename,O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (file_descriptor == -1) {
        printf("Failed To Open File To Append\n");
        exit(EXIT_FAILURE);
    }
    dup2(file_descriptor, 1); 
    close(file_descriptor);
    return 0;
}

int input_attach(char *filename) {
    int file_descriptor = open(filename,O_RDONLY);
    if (file_descriptor == -1) {
        printf("Failed To Open File To Read\n");
        exit(EXIT_FAILURE);
    }
    dup2(file_descriptor, STDIN_FILENO);
    close(file_descriptor);
    return 0;
}

// Here is for the functions to be added to the list
int (*operator_func[]) (char *) = {
  &output_write,
  &output_append,
  &input_attach
};

// All commands which need to run in the parent process (e.g. cd, since it needs to affect something about the parent directory) must be put in here

// write actual commands below this

int cd(char **args) { // this will either need changing, or need a system function creating when implanted into P-R
    if (args[1] == NULL) {
        printf("Expected Argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {//
        printf("Failed To Change Directory\n");    
        }
    }
    return 1;
}

int exit_rsh(char **args) {
    return 0;
}

// store commands indexed here. make sure order of commands matches in both arrays
char *builtin_str[] = {
  "cd",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &cd,
  &exit_rsh
};

int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

// end of parent process command area

char *read_line(void) {
    int buffer_size = 1024;
    int position = 0;
    char *buffer = malloc(sizeof(char)*buffer_size);
    int character;

    if (!buffer) { // if the buffer is of size 0, there has been an error and it has not been created correctly, so return an error
        printf("Buffer Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        character = getchar();
        
        if (character == EOF && position == 0) {
            free(buffer);
            printf("\n");
            exit(EXIT_SUCCESS);
        }

        if (character == EOF || character == '\n') { // if the character is end of file, or newline, then append an end of string character and return, otherwise, add the current character to the buffer
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = character;
        }
        position++;

        if (position >= buffer_size) { // if position reaches the end of the buffer, allocate more memory
            buffer_size += 1024;
            buffer = realloc(buffer, buffer_size);
            if (!buffer) {
                printf("Buffer Allocation Failed\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}



char **tokenize(char *line) {
    int buffer_size = 64;
    int position = 0;
    char **tokens = malloc(buffer_size * sizeof(char*));
    char *token;

    if (!tokens) {
        printf("Token Buffer Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= buffer_size) {
            buffer_size += 64;
            tokens = realloc(tokens, buffer_size * sizeof(char*));
            if (!tokens) {
                printf("Token Buffer Allocation Failed\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " \t\r\n");
    }
    tokens[position] = NULL;
    return tokens;
}
//------------------------------------//


int launch(char **args) {

    pid_t pid;
    pid_t wpid;
    int status;
    pid = fork();
    if (pid == 0) {

        int operator;
        int operator_flag = 0;
        int operator_index;
        for (int j = 0; args[j] != NULL; j++) {
            for (int i = 0; i < sizeof(operator_tokens)/sizeof(char *); i++) {
                if (strcmp(args[j], operator_tokens[i]) == 0) {

                    if (args[j+1] == NULL) {
                        printf("Redirection Missing File Argument\n");
                        exit(EXIT_FAILURE);
                    }

                    operator_flag = 1;
                    operator = i;
                    operator_index = j;

                    
                }
            }
        }
        
        if (operator_flag == 1) {
            
            operator_flag = 0;
            printf("hi");
            char *filename = args[operator_index+1];
            args[operator_index] = NULL;
            if (args[0] == NULL) {
                printf("Commands Cannot Begin With An Operator");
                exit(EXIT_FAILURE);
            }
            operator_func[operator](filename);
        }

        char binary_path[512];
        snprintf(binary_path, sizeof(binary_path), "%s%s", GLOBAL_BINARY_PATH, args[0]);
        if (execv(binary_path, args) == -1) {
            fprintf(stderr, "Failed to Execute %s\n", args[0]);
        }
        exit(EXIT_FAILURE);


    } else if (pid < 0) {
        printf("Error When Forking\n");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED); // waits for child to change state 
        } while (!WIFEXITED(status) && !WIFSIGNALED(status)); // ends loop if child finishes normally (wifexited) or otherwise (wifsignaled)
    }
    return 1;
}
//------------------------------------//

int execute(char **args) {
    if (args[0]==NULL) {
        return 1;
    }
    for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args); // if the command is in the builtin commands list, then call its function pointer and pass it the arguments
        }
    }
    return launch(args); // if not in builtins, pass the handling to launch()
}

void loop(void) { //shell loop
    int status;
    do {
        // char cwd[256]; could also use this but needs optimising, probably start string from ~ rather than / to shorten path a little.
        // getcwd(cwd, sizeof(cwd));
        // printf("%s> ", cwd);
        printf("> ");
        char *line = read_line();
        char **args = tokenize(line);
        status = execute(args);

        free(line);
        free(args);
    } while (status);

}
//------------------------------------//

// This function will be unnecessary when transplanting this into the OS, as we can just hardcode a path for command binaries to live in directly into it.
char *get_binary_directory(void) {
    char binary_path[256];
    static char result[264];
    
    ssize_t length = readlink("/proc/self/exe", binary_path, sizeof(binary_path) - 1);
    if (length == -1) {
        printf("Failed to Get Binary Path\n");
        exit(EXIT_FAILURE);
    }
    binary_path[length] = '\0';

    char *directory = dirname(binary_path);
    snprintf(result, sizeof(result), "%s/bin/", directory);
    return result;
}

int main(void) {
    GLOBAL_BINARY_PATH = get_binary_directory();
    signal(SIGINT, SIG_IGN); // stops interrupts affecting main shell. exiting requires exit to be called.
    printf("Welcome to RSH, Your Commands Are Located At: \"%s\"\n", GLOBAL_BINARY_PATH);
    loop();

}