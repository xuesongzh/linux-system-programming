/************************************************
*      Filename: write_fifo.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-14 06:32:19
* Last Modified: 2019-07-18 14:48:17
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
	int fifo_fd = open ("my_fifo", O_WRONLY);
	char buf[100];
	memset (buf, 0, 100);

	fgets (buf, 100, stdin);
	int write_len = write (fifo_fd, buf, strlen (buf));
	printf ("%d bytes have been sended to FIFO.\n", write_len);
	return 0;
}
