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
 * execute - Forks a child process to execute a command.
 * @path: The full path to the command to be executed.
 * @tokens: An array of argument strings for the command.
 * Return: 1 if the command was executed successfully.
 */

static int execute(const char *path, char **tokens)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (0);
	}
	if (pid == 0)
	{
		if (execve(path, tokens, environ) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

/**
 * executeCommand - Executes a non-built-in command using execve and PATH
 * @tokens: The array of arguments
 * Return: 1 if the command was executed successfully,
 * 0 if the command was not found
 */

int executeCommand(char **tokens)
{
	char *path, *path_copy, *dir, *full_path;
	size_t cmd_len;

	if (tokens[0][0] == '/' || strncmp(tokens[0], "./", 2) == 0
	|| strncmp(tokens[0], "../", 3) == 0)
	{
		if (access(tokens[0], X_OK) == 0)
			return (execute(tokens[0], tokens));
		return (0);
	}
	path = _getenv("PATH");
	if (!path)
		return (0);
	path_copy = strdup(path);
	if (!path_copy)
	{
		perror("strdup");
		return (0);
	}
	cmd_len = strlen(tokens[0]);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + cmd_len + 2);
		if (!full_path)
		{
			perror("malloc");
			free(path_copy);
			return (0); }
		snprintf(full_path, strlen(dir) + cmd_len + 2, "%s/%s", dir, tokens[0]);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			free(full_path);
			return (execute(full_path, tokens)); }
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (0);
}
