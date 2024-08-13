#include "main.h"

/**
 * handle_memory_error - Handle memory allocation errors
 * @tokens: Current array of tokens
 * @count: Number of tokens allocated
 * Return: NULL if failed, else previous tokens
 */
char **handle_memory_error(char **tokens, size_t count)
{
	for (size_t j = 0; j < count; j++)
		free(tokens[j]);
	free(tokens);
	return (NULL);
}

/**
 * tokenizeLine - Tokenize a line of input based on the specified delimiters
 * @argv: A pointer to the command-line arguments array
 * Return: An array of tokenized strings, or NULL on failure
 */

char **tokenizeLine(char **argv)
{
	if (argv == NULL || argv[0] == NULL)
		return (NULL);

	char *chain = argv[0];
	const char delimiters[] = " \t\n";
	char *token, **tokens = NULL;
	size_t count = 0;

	token = strtok(chain, delimiters);
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delimiters);
	}

		tokens = malloc(sizeof(char *) * (count + 1));
		if (tokens == NULL)
			return (NULL);

		token = strtok(chain, delimiters);
		for (size_t i = 0; i < count; i++)
		{
			if (token == NULL)
			{
				free(tokens);
				return (NULL);
			}
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
			return (handle_memory_error(tokens, i));
		token = strtok(NULL, delimiters);
	}

	tokens[count] = NULL;
	return (tokens);
}
