#include "main.h"

/**
 * read_stream - Read a line from the stream.
 *
 * Return: Pointer to the read line.
 */
char *read_stream(void)
{
    int buffer_size = 1024;
    int index = 0;
    char *line;
    int character;

    line = malloc(sizeof(char) * buffer_size);
    if (line == NULL)
    {
        fprintf(stderr, "Allocation error in read_stream");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        character = getchar();
        if (character == EOF)
        {
            free(line);
            exit(EXIT_SUCCESS);
        }
        else if (character == '\n')
        {
            line[index] = '\0';
            return line;
        }
        else
        {
            line[index] = character;
        }

        index++;

        if (index >= buffer_size)
        {
            buffer_size += buffer_size;
            line = realloc(line, buffer_size);
            if (line == NULL)
            {
                fprintf(stderr, "Reallocation error in read_stream");
                exit(EXIT_FAILURE);
            }
        }
    }
}

