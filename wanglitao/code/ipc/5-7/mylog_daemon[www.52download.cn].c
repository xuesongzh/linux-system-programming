/************************************************
*      Filename: mylog_daemon.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-14 06:36:55
* Last Modified: 2019-07-18 15:45:24
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define handle_error(msg) \
    {perror(msg);exit(EXIT_FAILURE);}
#define FIFO_SERVER "fifo_log_server"
#define LOG_PATHNAME    "/var/log/process.log"

int main (void)
{
	mkfifo (FIFO_SERVER, 0644);
	int ret_from_fork;
	char public_buf[100];
		
	int fifo_fd;
	fifo_fd = open (FIFO_SERVER, O_RDONLY);
	memset (public_buf, 0, 100);

	int fd;
	fd = open (LOG_PATHNAME, O_WRONLY | O_CREAT | O_APPEND);
    if (fd == -1)
        handle_error("open");
	int read_len;
	while (1)
	{
		read_len = read (fifo_fd, public_buf, 100);
		if (read_len == -1)
            handle_error("read")
		else if (read_len > 0)
		{
			printf ("%s\n", public_buf);
			write (fd, public_buf, strlen (public_buf));
		}
		else
		{
			sleep (3);
			continue;
		}
		sleep (1);
	}
	close (fd);
	return 0;
}
