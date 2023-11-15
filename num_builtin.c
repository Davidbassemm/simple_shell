#include "main.h"
/**
 * num_builtin - calc the num cmd
 * @bulitin: have the cmd
 *
 * Return: the result
 */
int num_builtin(char **bulitin)
{
	int count = 0;

	while (bulitin[count] != NULL)
	{
		count++;
	}
	return (count);
}
