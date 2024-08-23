#include <stdlib.h>
#include "main.h"

/**
 * exitShell - exits the shell with a given status
 * @tokens: array of tokens, where tokens[1] may contain the exit status
 * @line: the line variable from main
 * Return: this function does not return, it exits the program
 */
int exitShell(char **tokens, char *line)
{
	int status = 0;

	if (tokens[1] != NULL)
		status = atoi(tokens[1]);
	freeTokens(tokens);
	free(line);
	exit(status);
}
