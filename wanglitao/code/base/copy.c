
/************************************************
*      Filename: copy.c
*        Author: litao.wang
*   Description: 
*        Create: 2018-09-29 00:08:55
* Last Modified: 2018-10-10 18:47:44
*************************************************/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFFERSIZE 4096

int main (int argc, char *argv[])
{
	if (argc != 3)
	{
		printf ("usage:\n copy src dst\n");
		return 1;
	}

	int srcfd = open (argv[1], O_RDONLY);
	if (srcfd == -1)
	{
		perror ("open");
		return 1;
	}
	int dstfd = open (argv[2], O_CREAT|O_WRONLY, 0666);
	if (dstfd == -1)
	{
		perror ("open");
		return 1;
	}

	int len = 0;
	char buffer[BUFFERSIZE] = {0};
	while ((len = read(srcfd, buffer, BUFFERSIZE)) > 0)
	{
		if (write (dstfd, buffer, len) != len)
		{
			perror ("write error");
			return 2;
		}
	}
	if (len < 0)
	{
		perror ("read error");
		return 3;
	}
	close (srcfd);
	close (dstfd);
	return 0;
}
