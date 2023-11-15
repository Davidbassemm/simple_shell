#include "main.h"
/**
 * my_cd - function my cd
 * @arguments: have the command
 *
 * Return: 1 on success
 */
int my_cd(char **arguments)
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
 * my_env - function that prints env variable
 * @arguments: arguments
 *
 * Return: 1 on success 0 in otherwise
 */
int my_env(char **arguments)
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
 * my_exit - function
 * @arguments: have the commit
 *
 * Return: 0
 */
int my_exit(char **arguments)
{
	if (arguments[1])
	{
		return (atoi(arguments[1]));
	}
	else
	{
	return (0);
	}
}
/**
 * my_help - function helps the user
 * @arguments: have the command
 *
 * Return: 1 on success
 */
int my_help(char **arguments)
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

	for (c = 0 ; c < num_bulitin(bulitin) ; c++)
	{
		printf(" %s - %s\n", bulitin[c], des[c]);
	}
	return (1);
}
