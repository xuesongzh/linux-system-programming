/************************************************
*      Filename: fifo_demo.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-14 06:36:55
* Last Modified: 2019-07-18 15:03:34
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main (void)
{
	mkfifo ("my_fifo", 0644);
	int ret_from_fork;
	int fifo_fd;
	ret_from_fork = fork ();
	if (ret_from_fork == -1)
	{
		perror ("fork");
		exit (EXIT_FAILURE);
	}
	else if (ret_from_fork == 0)
	{
		fifo_fd = open ("my_fifo", O_WRONLY);
		char buf[100];
		memset (buf, 0, 100);
		printf ("child process(%d) input msg:", getpid ());
		fgets (buf, 100, stdin);
		int write_len = write (fifo_fd, buf, strlen (buf));
		printf ("%d bytes hace been sent\n", write_len);
		_exit (EXIT_SUCCESS);
	}
	else
	{
		sleep (1);
		fifo_fd = open ("my_fifo", O_RDONLY);
		char buf[100];
		memset (buf, 0, 100);
		read (fifo_fd, buf, 100);
		printf ("parent process(%d) read msg from FIFO: %s\n", getpid (), buf);
		exit (EXIT_SUCCESS);
	}
	return 0;
}
