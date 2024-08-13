#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

char **handle_memory_error(char **tokens, size_t count);
char **tokenizeLine(char **argv);

#endif
