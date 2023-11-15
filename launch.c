#include "main.h"

/**
 * launch - Function that takes charge of processing.
 * @args: Command arguments.
 *
 * Return: -1 on failure.
 */
int launch(char **args)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("Error in launch: child process");
        }
        exit(EXIT_FAILURE);
    }
    else if (child_pid < 0)
    {
        perror("Error in launch: forking");
    }
    else
    {
        do {
            waitpid(child_pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return -1;
}
