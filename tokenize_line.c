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
	char **tokens = malloc(size * sizeof(char *));
	char *token = NULL;
	int i = 0, j;

	if (tokens == NULL)
		return (NULL);

	while ((token = strtok(str, " ")))
	{
		str = NULL;
		if (token[0] == '-' && token[1] != '\0')
		{
			for (j = 1; token[j] != '\0'; j++)
			{
				if (i >= size)
					tokens = realloc(tokens, (size *= 2) * sizeof(char *));
				if (tokens == NULL)
					return (NULL);
				tokens[i++] = strndup(&token[j], 1);
			}
		}
		else
			tokens[i++] = strdup(token);
	}
	tokens[i] = NULL;
	return (tokens);
}
