#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

/**
 * struct builtIn_s - Represents a built-in command in a shell.
 * @name: The name of the built-in command.
 * @handler: The function to execute when the built-in command is called.
 */

typedef struct builtIn_s
{
	char *name;
	int (*handler)(char **tokens, char *line);
} builtIn;

int _feof(int fd);
void freeTokens(char **tokens);
char **tokenizeLine(char *str);
int executeCommand(char **tokens);
int exitShell(char **tokens, char *line);
int printEnv(char **tokens, char *line);

#endif
