/************************************************
*      Filename: dup2.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: redirect stdout to specified file
*        Create: 2019-06-21 09:37:22
* Last Modified: 2019-07-17 16:38:01
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define handler_error(msg) \
    {perror(msg);exit(EXIT_FAILURE);}

int main (void)
{
	int fd, new_fd;
	char *buf = "hello world\n";

	fd = open ("data.log", O_RDWR | O_CREAT, 0644);
	if (fd == -1)
        handler_error("open");

	new_fd = dup2 (fd, 1);
	if (new_fd == -1)
        handler_error("dup2");

	printf ("fd: %d\n new_fd: %d\n", fd, new_fd);
	write (1, buf, strlen(buf));
	close (fd);

	return 0;
}
