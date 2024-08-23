#include "main.h"

/**
 * tokenizeLine - Tokenizes a string into words.
 * @str: The input string to tokenize.
 * Return: A dynamically allocated array of strings containing the tokens.
 * NULL if memory allocation fails.
 */

char **tokenizeLine(char *str)
{
	int i = 0, j = 0;
	size_t size = 10;
	char **tokens = NULL, *token = NULL, *p = NULL;

	if (str == NULL)
		return (NULL);

	tokens = malloc(size * sizeof(char *));
	if (tokens == NULL)
		return (NULL);

	token = strtok(str, " ");
	while (token != NULL)
	{
		if ((size_t) i >= size)
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

		if (token[0] == '-')
		{
			for (p = token + 1; *p != '\0'; p++)
			{
				tokens[i] = malloc(3 * sizeof(char));
				if (tokens[i] == NULL)
				{
					for (j = 0; j < i; j++)
						free(tokens[j]);
					free(tokens);
					return (NULL);
				}
				tokens[i][0] = '-';
				tokens[i][1] = *p;
				tokens[i][2] = '\0';
				i++;
			}
		}
		else
		{
			tokens[i++] = strdup(token);
		}

		token = strtok(NULL, " ");
	}

	tokens[i] = NULL;
	return (tokens);
}