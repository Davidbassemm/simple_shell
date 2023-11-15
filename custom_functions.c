#include "main.h"
/**
 * custom_cd - function my cd
 * @arguments: have the command
 *
 * Return: 1 on success
 */
int custom_cd(char **arguments)
{
	if (arguments[1] == NULL)
	{
		fprintf(stderr, "expected argument to 'cd'\n");
	}
	else
	{
		if (chdir(arguments[1]) != 0)
		{
			perror("error in my_cd");
		}
	}
	return (-1);
}
/**
 * custom_env - function that prints env variable
 * @arguments: arguments
 *
 * Return: 1 on success 0 in otherwise
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
	return (-1);

}
/**
 * custom_exit - function
 * @arguments: have the commit
 *
 * Return: 0
 */
int custom_exit(char **args) 
{
    if (args[1]) {
        exit(atoi(args[1]));
    } else {
        exit(0);
    }
}

/**
 * custom_help - function helps the user
 * @arguments: have the command
 *
 * Return: 1 on success
 */
int custom_help(char **arguments)
{
	int c;


	char *bulitin[13] = {
		"cd",
		"env",
		"help",
		"exit"
	};
	char *des[] = {
		"change the current dir",
		"display inf about the blitin comd",
		"exit the shell:"
		};
	(void)arguments;
	printf("simple shell\n");
	printf("------------\n");
	printf("A basic shell imolementation.\n\n");
	printf("Duilt-in cmd:\n");

	for (c = 0 ; c < num_builtin(bulitin) ; c++)
	{
		printf(" %s - %s\n", bulitin[c], des[c]);
	}
	return (1);
}
