#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "main.h"

/**
 * main - main program entry point
 * @argc: the argument count
 * @argv: the argument vector
 * Return: 0 if successful
 */
int main(void)
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
        {
            commandFound = executeCommand(tokens);
            if (!commandFound)
            {
                fprintf(stderr, "./hsh: 1: %s: not found\n", tokens[0]);
                freeTokens(tokens);
                free(line);
                exit(127);
            }
        }

        freeTokens(tokens);
    }

    free(line);
    return (0);
}

