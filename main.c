#include "main.h"
/**
 * main - function that is the entry point of the program
 *@argc: counter
 *@argv: array of string
 * Return: exit succuss
 */

int main(int argc, char **argv)
{
	if (isatty(STDIN_FILENO) == 1)
	{
		inter();
	}
	else
	{
		non_inter();
	}
	(void)(argc);
	(void)(argv);
	return (0);
}
