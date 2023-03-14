#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
int main (int argc, char *argv[])
{
	struct iovec iov[3];
	ssize_t count;
	int fd;
	int i;
	char *buf[] = {
		"hello world!\n", 
		"hello Ubuntu\n", 
		"hello Linux!\n"
	};
	fd = open (argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror ("open");
		return -1;
	}
	for (i = 0; i < 3; i++)
	{
		iov[i].iov_base = buf[i];
		iov[i].iov_len = strlen (buf[i]) + 1;
		printf ("iov[%d] size: %d\n", i, iov[i].iov_len);
	}

	count = writev (fd, iov, 3);
	if (count == -1)
	{
		perror ("writev");
		return -1;
	}
	
	close (fd);
	if (fd == -1)
	{
		perror ("close");
		return -1;
	}
	return 0;
}
