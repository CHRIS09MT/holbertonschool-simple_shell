#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

/**
 * _feof - Checks if the end-of-file has been reached for fd
 * @fd: The file descriptor to check.
 * Return: 1 if EOF is reached, 0 otherwise.
 */
int _feof(int fd)
{
	struct stat file_stat;
	off_t current_offset;

	current_offset = lseek(fd, 0, SEEK_CUR);
	if (current_offset == -1)
	{
		if (errno == ESPIPE)
			return (0);
		perror("lseek failed");
		return (-1);
	}

	if (fstat(fd, &file_stat) == -1)
	{
		perror("fstat failed");
		return (-1);
	}

	if (current_offset >= file_stat.st_size)
		return (1);

	return (0);
}
