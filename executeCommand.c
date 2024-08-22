#include "main.h"

/**
 * _getenv - mimics getenv()
 * @name: the name of the environment variable
 * Return: the part of the env variable after the = sign or null if failed
*/
char *_getenv(const char *name)
{
	char **env = NULL;

	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, name, strlen(name)) == 0
		&& (*env)[strlen(name)] == '=')
		{
			return (*env + strlen(name) + 1);
		}
	}
	return (NULL);
}

/**
 * _getFullPath - Constructs the full path of a command.
 * @tokens: The array of arguments, where the first token is the command name.
 * Return: A pointer to the full path of the command, or NULL if not found.
 */

char *_getFullPath(char **tokens)
{
	char *path, *path_copy, *dir, *full_path;
	size_t cmd_len, dir_len;

	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}
	cmd_len = strlen(tokens[0]);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		dir_len = strlen(dir);
		full_path = malloc(dir_len + cmd_len + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			return (NULL);
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, tokens[0]);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * executeCommand - Executes a non-built-in command using execve and PATH
 * @tokens: The array of arguments
 * Return: 1 if the command was executed successfully,
 * 0 if the command was not found
 */

int executeCommand(char **tokens)
{
	pid_t pid;
	int status;
	char *full_path;

	if (tokens[0][0] == '/' || strncmp(tokens[0], "./", 2) == 0
	|| strncmp(tokens[0], "../", 3) == 0)
	{
		full_path = tokens[0];
	}
	else
	{
		full_path = _getFullPath(tokens);
		if (full_path == NULL)
		return (0);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		if (full_path != tokens[0])
			free(full_path);
		return (0);
	} else if (pid == 0)
	{
		if (execve(full_path, tokens, environ) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	} else
	{
		do {
		waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	if (full_path != tokens[0])
		free(full_path);
	return (1);
}
