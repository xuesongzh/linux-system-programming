
/************************************************
*      Filename: file_read.c
*        Author: litao.wang
*   Description: 
*        Create: 2018-09-28 07:38:23
* Last Modified: 2018-10-10 18:46:53
*************************************************/
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
	int fd;
	fd = open ("hello.txt", O_RDWR|O_CREAT, 0666);
	if (fd == -1)
	{
		printf ("open file failed!\n");
		return -1;
	}

	char string[20] = "hello world!\n";
	write (fd, string, 14);
	fsync(fd);

	char *buf = (char*)malloc (20);
	memset (buf, 0, 20);
	lseek (fd, 0, SEEK_SET);
	read (fd, buf, 14);
	printf ("%s", buf);

	free (buf);
	close (fd);
	return 0;
}
