#include "main.h"

/**
 * freeTokens - Frees memory allocated for tokens
 * @tokens: array of strings to be freed
 */

void freeTokens(char **tokens)
{
	int i = 0;

	if (tokens == NULL)
		return;

    for (i = 0; tokens[i] != NULL; i++)
    {
        free(tokens[i]);
    }
    free(tokens);
}
