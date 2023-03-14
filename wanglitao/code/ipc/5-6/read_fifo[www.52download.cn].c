/************************************************
*      Filename: read_fifo.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-14 06:36:55
* Last Modified: 2019-07-18 14:47:25
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main (int argc, char *argv[])
{
	mkfifo ("my_fifo", 0644);

	int fifo_fd = open ("my_fifo", O_RDONLY);

	char buf[100];
	memset (buf, 0, 100);
	read (fifo_fd, buf, 100);
	printf ("Read from FIFO: %s\n", buf);

	return 0;
}
