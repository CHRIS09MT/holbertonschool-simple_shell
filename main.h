#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

typedef struct builtIn_s
{
    char *name;
    int (*handler)(char **tokens);
} builtIn;

void freeTokens(char **tokens);
char **tokenizeLine(char *str);
int exitShell(char **tokens);
int printEnv(char **tokens);

#endif
