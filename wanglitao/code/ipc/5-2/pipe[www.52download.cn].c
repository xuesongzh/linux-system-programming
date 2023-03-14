/************************************************
*      Filename: pipe.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-14 06:05:29
* Last Modified: 2019-07-17 15:16:03
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define handle_error(msg) \
    {perror(msg);exit(EXIT_FAILURE);}

int main (int argc, char *argv[])
{
	int pipe_fd[2]; 
	if (pipe (pipe_fd) == -1) 
        handle_error("pipe");

	int ret_from_fork;
	ret_from_fork = fork ();
	if (ret_from_fork == -1)
        handle_error("fork");

	if (ret_from_fork == 0)   //child process
	{
		char str[100] = {0}; 
		printf("child process:\n input string:");
		scanf ("%s", str);
		//gets(str);
		write (pipe_fd[1], str, strlen (str)); // write data to pipe
		close (pipe_fd[1]);
		_exit (EXIT_SUCCESS);
	}

	if (ret_from_fork > 0)   // parent process
	{
		char buf[30] = {0};
		read (pipe_fd[0], buf, 30); // read data from pipe
		printf ("parent process: %s\n", buf);
		close (pipe_fd[0]);
		exit (EXIT_SUCCESS);
	}

	return 0;
}
