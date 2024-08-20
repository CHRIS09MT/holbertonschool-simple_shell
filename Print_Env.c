#include "main.h"

/**
 * printEnv Function to print environment variables.
 * Return: 0 on success
 */

int printEnv()
{
	extern char **environ;
	int i = 0;

	for (; environ[i] != NULL; i++)
                printf("%s\n", environ[i]);

	return (0);
}
