#include "main.h"

/**
 * execute - Execute the command.
 * @arguments: Command arguments.
 *
 * Return: Result of the function launch.
 */
int execute(char **arguments)
{
    int (*builtin_func[])(char **) = {
        &custom_cd,
        &custom_env,
        &custom_help,
        &custom_exit
    };

    char *builtin[] = {
        "cd",
        "env",
        "help",
        "exit"
    };

    if (arguments[0] == NULL)
        return -1;

    for (int c = 0; c < num_builtin(builtin); c++)
    {
        if (strcmp(arguments[0], builtin[c]) == 0)
            return (*builtin_func[c])(arguments);
    }

    return launch(arguments);
}
