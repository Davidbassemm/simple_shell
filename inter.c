#include "main.h"

/**
 * interactive - Check if interactive or not.
 *
 * Return: Nothing.
 */
void inter(void)
{
    char *input_line;
    char **args;
    int status = -1;

    do {
        printf("-> ");
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
