#include "main.h"

/**
 * tokenizeLine - Function to tokenize a line
 * @argv: A pointer to the command-line arguments array
 * Return: A pointer to the tokenized line
 */

char **tokenizeLine(char **argv)
{
	if (argv[0] == NULL || argv == NULL)
		return (NULL);

	char *chain = argv[0];
	const char delimiter[] = " ";
	char *token, **tokens = NULL;
	size_t count = 0, j = 0;

	token = strtok(chain, delimiter);

	while (token != NULL)
	{
		tokens = realloc(tokens, sizeof(char *) * (count + 1));
		if (tokens == NULL)
		{
			for (; j < count; j++)
				free(tokens[j]);
			return (NULL);
		}

		tokens[count] = strdup(token);
		if (tokens[count] == NULL)
		{
			for (; j < count; j++)
				free(tokens[j]);
			return (NULL);
		}

		count++;
		token = strtok(NULL, delimiter);
	}

	tokens = realloc(tokens, sizeof(char *) * (count + 1));
	if (tokens != NULL)
		tokens[count] = NULL;

	return (tokens);
}
