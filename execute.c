#include "main.h"
/**
 * execute - exe the cmd
 * @arguments: have the comamnd
 *
 * Return: the func lanuch
 */
int execute(char **arguments)
{
	int (*bulitin_func[])(char **) = {
		&custom_cd,
		&custom_env,
		&custom_help,
		&custom_exit
	};

	char *bulitin[13] = {
		"cd",
		"env",
		"help",
		"exit"
	};
	int c;

	if (arguments[0] == NULL)
		return (-1);
	for (c = 0 ; c < num_builtin(bulitin) ; c++)
	{
		if (strcmp(arguments[0], bulitin[c]) == 0)
		{
			return ((*bulitin_func[c])(arguments));
		}
	}
	return (launch(arguments));
}
