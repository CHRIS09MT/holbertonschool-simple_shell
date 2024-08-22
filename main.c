#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "main.h"

/**
 * handleBuiltinExecution - helper function, checks if command is builtin
 * @tokens: the tokens from main
 * @line: the line from main
 * @handlers: the handlers from main
 * Return: 1 if built int was found, 0 if  not
*/
int handleBuiltinExecution(char **tokens, char *line, builtIn *handlers)
{
	int i;
	int commandFound = 0;

	for (i = 0; handlers[i].name != NULL; i++)
	{
		if (strcmp(handlers[i].name, tokens[0]) == 0)
		{
			commandFound = 1;
			if (handlers[i].handler(tokens, line) == 0)
			{
				freeTokens(tokens);
				free(line);
				return (commandFound);
			}
			break;
		}
	}
	return (commandFound);
}

/**
 * handleCommandExecution - helper function, tries to execute command
 * @tokens: the tokens from main
 * @line: the line from main
 * @interactive: the interactive 'bool' from main
 */
void handleCommandExecution(char **tokens, char *line, int interactive)
{
	int commandFound;

	commandFound = executeCommand(tokens);
	if (!commandFound)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", tokens[0]);
		if (!interactive)
		{
			freeTokens(tokens);
			free(line);
			exit(127);
		}
	}
}

/**
 * main - main program entry point
 * Return: 0 if successful
 */
int main(void)
{
	int interactive = 1, commandFound = 0;
	size_t len = 0;
	ssize_t read;
	char *line = NULL, **tokens = NULL;
	builtIn handlers[] = {{"exit", exitShell}, {"env", printEnv}, {NULL, NULL}};

	if (!isatty(STDIN_FILENO))
		interactive = 0;
	while (1)
	{
		commandFound = 0;
		if (interactive)
			printf("SimpleShell$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (!interactive || errno == 0)
				break;
			perror("getline failed");
			continue;
		}
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		tokens = tokenizeLine(line);
		if (tokens == NULL || tokens[0] == NULL)
		{
			freeTokens(tokens);
			continue;
		}
		commandFound = handleBuiltinExecution(tokens, line, handlers);
		if (!commandFound)
			handleCommandExecution(tokens, line, interactive);
		freeTokens(tokens);
	}
	free(line);
	return (0);
}

