#include "main.h"

/**
 * tokenizeLine - Tokenizes a string into words.
 * @str: The input string to tokenize.
 * Return: A dynamically allocated array of strings containing the tokens.
 * NULL if memory allocation fails.
 */

char **tokenizeLine(char *str)
{
	int i = 0;
	size_t size = 10;
	char **tokens = NULL, *token, *p, **new_tokens;

	if (!str)
		return (NULL);

	tokens = malloc(size * sizeof(char *));
	if (!tokens)
		return (NULL);
	token = strtok(str, " ");
	while (token)
	{
		if (i >= (int)size)
		{
			size *= 2;
			new_tokens = realloc(tokens, size * sizeof(char *));
			if (!new_tokens)
			{
				while (i > 0) free(tokens[--i]);
				free(tokens);
				return (NULL);
			}
			tokens = new_tokens;
		}
		if (*token == '-')
		{
			for (p = token + 1; *p; p++, i++)
			{
				tokens[i] = malloc(3);
				if (!tokens[i])
				{
					while (i > 0) free(tokens[--i]);
					free(tokens);
					return (NULL);
				}
				tokens[i][0] = '-';
				tokens[i][1] = *p;
				tokens[i][2] = '\0';
			}
		}
		else
		{
			tokens[i] = strdup(token);
			if (!tokens[i])
			{
				while (i > 0) free(tokens[--i]);
				free(tokens);
				return (NULL);
			}
			i++;
		}
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return (tokens);
}
