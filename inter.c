#include "main.h"
/**
 * inter - function cheac if interactive or not
 *
 * Return: noting
 */
void inter(void)
{
	char *line;
	char **arguments;
	int stat = -1;

	do {
		printf("-> ");
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
