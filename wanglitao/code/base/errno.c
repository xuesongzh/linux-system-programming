
/************************************************
*      Filename: errno.c
*        Author: litao.wang
*   Description: 
*        Create: 2018-10-10 12:20:20
* Last Modified: 2018-10-11 03:38:02
*************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
	int fd;

	fd = open ("hello.dat", O_WRONLY);
	if (fd == -1)
	{
		perror ("open hello.dat failed!");
		return -1;
	}
	close (fd);
	return 0;
}
