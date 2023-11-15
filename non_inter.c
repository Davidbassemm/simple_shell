#include "main.h"

/**
 * non_interactive - Check if in non-interactive mode.
 *
 * Return: Nothing.
 */
void non_inter(void)
{
    char *input_line;
    char **args;
    int status = -1;

    do {
        input_line = read_line();
        args = split_line(input_line);
        status = execute(args);
        free(input_line);
        free(args);
        if (status >= 0)
        {
            exit(status);
        }
    } while (status == -1);
}
