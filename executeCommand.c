#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * _getenv - mimics getenv()
 * name: the name of the environment variable
 * Return: the part of the env variable after the = sign or null if failed
*/
char *_getenv(const char *name)
{
	extern char **environ;
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
 * executeCommand - Executes a non-built-in command using execve and PATH
 * @tokens: The array of arguments
 * Return: 1 if the command was executed successfully,
 * 0 if the command was not found
 */
int executeCommand(char **tokens)
{
	extern char **environ;
	pid_t pid;
	int status;
	char *path, *path_copy, *dir, *full_path;
	size_t cmd_len, dir_len;

	if (tokens[0][0] == '/' || strncmp(tokens[0], "./", 2) == 0
	|| strncmp(tokens[0], "../", 3) == 0)
	{
		if (access(tokens[0], X_OK) == 0)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork failed");
				return (0);
			}
			else if (pid == 0)
			{
				if (execve(tokens[0], tokens, environ) == -1)
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
	}

	path = _getenv("PATH");
	if (path == NULL)
		return (0);

	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup");
		return (0);
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
			return (0);
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, tokens[0]);

		if (access(full_path, X_OK) == 0)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork failed");
				free(full_path);
				free(path_copy);
				return (0);
			}
			else if (pid == 0)
			{
				if (execve(full_path, tokens, environ) == -1)
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

			free(full_path);
			free(path_copy);
			return (1);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (0);
}
