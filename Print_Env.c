#include "main.h"

/**
 * printEnv - Function to print environment variables.
 * @tokens: Unused parameter. This function does not use this argument.
 * @line: the line variable from main
 * Return: always 1
 */

int printEnv(char **tokens, char *line)
{
	int i = 0;
	(void) tokens;
	(void) line;

	for (; environ[i] != NULL; i++)
		printf("%s\n", environ[i]);

	return (1);
}
