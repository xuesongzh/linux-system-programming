
/************************************************
*      Filename: fb.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2018-12-09 09:14:38
* Last Modified: 2018-12-10 00:34:40
*************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main (void)
{
	int fd;
	unsigned char *fb_mem;
	int i = 100;
	fd = open ("/dev/fb0", O_RDWR);
	if (fd == -1)
	{
		perror ("open");
		return -1;
	}
	fb_mem = mmap (NULL, 800*600, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (fb_mem == MAP_FAILED)
	{
		perror ("mmap");
		return -1;
	}
	while (1)
	{
		memset (fb_mem, i++, 800*600);
		sleep (1);
	}

	close (fd);
	return 0;
}
