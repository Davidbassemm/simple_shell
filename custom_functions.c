#include "main.h"

/**
 * custom_cd - Custom implementation of 'cd' command.
 * @arguments: Command arguments.
 *
 * Return: 1 on success, -1 on failure.
 */
int custom_cd(char **arguments)
{
    if (arguments[1] == NULL)
    {
        fprintf(stderr, "Expected argument to 'cd'\n");
    }
    else
    {
        if (chdir(arguments[1]) != 0)
        {
            perror("Error in custom_cd");
        }
        else
        {
            return 1;
        }
    }
    return -1;
}

#include "main.h"

/**
 * custom_env - Custom function that prints environment variables.
 * @arguments: Command arguments.
 *
 * Return: 1 on success, 0 otherwise.
 */
int custom_env(char **arguments)
{
    int c = 0;
    (void)(**arguments);

    while (environ[c])
    {
        write(STDOUT_FILENO, environ[c], strlen(environ[c]));
        write(STDOUT_FILENO, "\n", 1);
        c++;
    }
    return -1;
}

#include "main.h"

/**
 * custom_exit - Custom exit function.
 * @arguments: Command arguments.
 *
 * Return: 0 if no argument, or the exit status specified.
 */
int custom_exit(char **arguments)
{
    if (arguments[1])
    {
        return atoi(arguments[1]);
    }
    else
    {
        return 0;
    }
}

#include "main.h"

/**
 * custom_help - Custom help function.
 * @arguments: Command arguments.
 *
 * Return: 1 on success.
 */
int custom_help(char **arguments)
{
    int c;

    char *builtin[13] = {
        "cd",
        "env",
        "help",
        "exit"
    };
    char *descriptions[] = {
        "Change the current directory",
        "Display information about built-in commands",
        "Exit the shell"
    };

    (void)arguments;
    printf("Simple Shell\n");
    printf("------------\n");
    printf("A basic shell implementation.\n\n");
    printf("Built-in commands:\n");

    for (c = 0; c < num_builtin(builtin); c++)
    {
        printf(" %s - %s\n", builtin[c], descriptions[c]);
    }
    return 1;
}

