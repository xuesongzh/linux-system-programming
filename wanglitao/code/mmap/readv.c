#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
int main (int argc, char *argv[])
{
	char buf1[14], buf2[14], buf3[14];
	struct iovec iov[3];
	ssize_t count;
	int fd;
	
	fd = open (argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror ("open");
		return -1;
	}

	iov[0].iov_base = buf1;
	iov[0].iov_len  = sizeof (buf1);
	iov[1].iov_base = buf2;
	iov[1].iov_len  = sizeof (buf2);
	iov[2].iov_base = buf3;
	iov[2].iov_len  = sizeof (buf3);

	count = readv (fd, iov, 3);
	if (count == -1)
	{
		perror ("readv");
		return -1;
	}
	
//	for (int i = 0; i < 3; i++)
//		printf ("%s", (char *)iov[i].iov_base);
	printf ("%s", (char *) &buf1);
	printf ("%s", (char *) &buf2);
	printf ("%s", (char *) &buf3);
	
	close (fd);
	if (fd == -1)
	{
		perror ("close");
		return -1;
	}
	return 0;
}
