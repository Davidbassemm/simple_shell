#include "main.h"

/**
 * num_builtin - Calculate the number of built-in commands.
 * @builtin: Array of built-in commands.
 *
 * Return: The number of built-in commands.
 */
int num_builtin(char **builtin)
{
    int count = 0;

    while (builtin[count] != NULL)
    {
        count++;
    }
    return count;
}
