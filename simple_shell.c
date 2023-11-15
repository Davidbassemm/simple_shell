// simple_shell.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>  // Add this line for strcspn

#define MAX_COMMAND_LENGTH 1024

void display_prompt() {
    printf("#cisfun$ ");
    fflush(stdout);
}

int main(void) {
    char command[MAX_COMMAND_LENGTH];
    pid_t child_pid;
    int status;

    while (1) {
        display_prompt();

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\n");
            break; // handle Ctrl+D (end of file)
        }

        // Remove the trailing newline character
        command[strcspn(command, "\n")] = '\0';

        child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) { // Child process
            execlp(command, command, (char *)NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
        } else { // Parent process
            waitpid(child_pid, &status, 0);

            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                fprintf(stderr, "./shell: %s: command not found\n", command);
            }
        }
    }

    return EXIT_SUCCESS;
}
