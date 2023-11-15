#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

/**
 * struct Command - Represents a command entered by the user
 * @args: An array of strings containing the command and its arguments
 */
typedef struct Command {
    char *args[MAX_ARG_SIZE];
} Command;

/**
 * struct Shell - Represents the state of the shell
 * @prompt: The shell prompt
 * @exit_flag: Flag to indicate if the shell should exit
 */
typedef struct Shell {
    char *prompt;
    int exit_flag;
} Shell;

/**
 * Function Declarations
 */

/* main.c */
void initialize_shell(Shell *shell);
void display_prompt(const Shell *shell);
void read_command(Command *cmd);

/* execute.c */
void execute_command(const Command *cmd);

/* utils.c */
void free_command(Command *cmd);

#endif /* SHELL_H */

