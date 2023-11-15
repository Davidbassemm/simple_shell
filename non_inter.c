#include "main.h"
/**
 * non_interactive - cheac if in non interactive mode or not
 *
 * Return: noting
 */
void non_inter(void)
{
	char *line;
	char **arguments;
	int stat = -1;

	do {
		line = read_line();
		arguments = split_line(line);
		stat = execute(arguments);
		free(line);
		free(arguments);
		if (stat >= 0)
		{
			exit(stat);
		}
	} while (stat == -1);
}
