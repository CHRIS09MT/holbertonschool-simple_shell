#include "main.h"

/**
 * exitShell - just returns 0 to signal that the shell should exit
 * @tokens: unused, the signature of all built-ins
 * Return: always 0 to signal shell should exit
 */
int exitShell(char **tokens)
{
    (void)tokens;
    return 0;
}
