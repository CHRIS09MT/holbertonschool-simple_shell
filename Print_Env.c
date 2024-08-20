#include "main.h"

/**
 * printEnv Function to print environment variables.
 * Return: 0 on success
 */

int printEnv(char **tokens)
{
	extern char **environ;
	int i = 0;
	(void) tokens;

	for (; environ[i] != NULL; i++)
                printf("%s\n", environ[i]);

	return (1);
}
