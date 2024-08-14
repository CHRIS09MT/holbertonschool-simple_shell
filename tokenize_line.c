#include "main.h"

/**
 * tokenizeLine - Tokenize a line of text into words.
 * @str: The input text string containing the line to tokenize.
 * Return: An array of pointers to strings (tokens), or NULL if that fails.
 */

char **tokenizeLine(char *str)
{
	if (str == NULL)
		return (NULL);

	size_t size = 10;
	char **tokens = NULL;
	char *token = NULL;
	int i = 0, j = 0;

	tokens = malloc(size * sizeof(char *));
	if (tokens == NULL)
		return (NULL);

	token = strtok(str, " ");
	if (token != NULL)
		tokens[i++] = strdup(token);

	while ((token = strtok(NULL, " ")) != NULL)
	{
		if (i >= size)
		{
			size *= 2;
			tokens = realloc(tokens, size * sizeof(char *));
			if (tokens == NULL)
			{
				for (j = 0; j < i; j++)
					free(tokens[j]);
				free(tokens);
				return (NULL);
			}
		}
		tokens[i++] = strdup(token);
	}

	tokens[i] = NULL;

	return (tokens);
}
