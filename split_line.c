#include "main.h"

/**
 * split_line - Split the input line into tokens.
 * @input_line: String to be split.
 *
 * Return: Array of tokens.
 */
char **split_line(char *input_line)
{
    int buffer_size = 64;
    int index = 0;
    char **tokens;
    char *token;
    char *delimiter = " \t\r\n\a";

    tokens = malloc(sizeof(char *) * buffer_size);
    if (!tokens)
    {
        fprintf(stderr, "Allocation error in split_line\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(input_line, delimiter);
    while (token != NULL)
    {
        if (token[0] == '#')
        {
            break;
        }

        tokens[index] = token;
        index++;

        if (index >= buffer_size)
        {
            buffer_size += buffer_size;
            tokens = realloc(tokens, sizeof(char *) * buffer_size);
            if (!tokens)
            {
                fprintf(stderr, "Reallocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, delimiter);
    }

    tokens[index] = NULL;
    return tokens;
}

