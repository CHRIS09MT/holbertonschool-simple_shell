#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * main - main program entry point
 * @argc: the argument count
 * @argv: the argument vector
 * Return: 0 if successful
 */
int main(int argc, char **argv)
{
	int i;
	int interactive = 1, commandFound = 0;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **tokens = NULL;
	builtIn handlers[] = {
		{"exit", exitShell},
		{"env", printEnv},
		{NULL, NULL}};

	(void) argv; /*quitar cuando implementemos modo no-interactivo*/
	if (argc != 1)
		interactive = 0;
	while (interactive)
	{
		commandFound = 0;
		printf("SimpleShell $ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			perror("getline");
			break;
		}
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		tokens = tokenizeLine(line);
		if (tokens == NULL || tokens[0] == NULL)
		{
			freeTokens(tokens);
			continue;
		}
		for (i = 0; handlers[i].name != NULL; i++)
		{
			if (strcmp(handlers[i].name, tokens[0]) == 0)
			{
				commandFound = 1;
				if (handlers[i].handler(tokens) == 0)
				{
					freeTokens(tokens);
					free(line);
					return (0);
				}
				break;
			}
		}
		if (!commandFound)
			printf("%s: Command does not exist.\n", tokens[0]);
		freeTokens(tokens);
	}
	free(line);
	return (0);
}
