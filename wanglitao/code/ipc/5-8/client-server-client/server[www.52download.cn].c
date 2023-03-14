/************************************************
*      Filename: server.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-14 06:36:55
* Last Modified: 2019-07-18 19:09:29
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_SERVER "fifo_server"
#define FIFO_CLIENT_1 "fifo_client1"
#define FIFO_CLIENT_2 "fifo_client2"

int main (void)
{
	mkfifo (FIFO_SERVER, 0644);
	mkfifo (FIFO_CLIENT_1, 0644);
	mkfifo (FIFO_CLIENT_2, 0644);
	int ret_from_fork;
	int buf_ready = 0;
	char public_buf[100];
		
	int fifo_fd_read;
	fifo_fd_read = open (FIFO_SERVER, O_RDONLY);
	memset (public_buf, 0, 100);

	int fifo_fd_write1;
	int fifo_fd_write2;
	fifo_fd_write1 = open (FIFO_CLIENT_1, O_WRONLY);
	fifo_fd_write2 = open (FIFO_CLIENT_2, O_WRONLY);
	int read_len;
	while (1)
	{
		read_len = read (fifo_fd_read, public_buf, 100);
		if (read_len == -1)
		{
			perror ("read");
			exit (EXIT_FAILURE);
		}
		else if (read_len > 0)
		{
			printf ("%s\n", public_buf);
			if (public_buf[0] == '1')
				write (fifo_fd_write1, public_buf + 1, strlen (public_buf));
			else if (public_buf[0] == '2')
				write (fifo_fd_write2, public_buf + 1, strlen (public_buf));
		}
		sleep (1);
	}
	return 0;
}
