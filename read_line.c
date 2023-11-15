#include "main.h"

/**
 * read_line - Read a line from stdin.
 *
 * Return: Pointer to the allocated string.
 */
char *read_line(void)
{
    size_t buffer_size = 0;
    char *line = NULL;

    if (getline(&line, &buffer_size, stdin) == -1)
    {
        if (feof(stdin))
        {
            free(line);
            exit(EXIT_SUCCESS);
        }
        else
        {
            free(line);
            perror("Error while reading the line from stdin");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}
