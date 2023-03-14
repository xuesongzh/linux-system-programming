/************************************************
*      Filename: pipe-dup.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-21 10:18:31
* Last Modified: 2019-07-17 17:37:48
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void)
{
	int pipe_fd[2];
	if (pipe (pipe_fd) == -1)
	{
		perror ("pipe");
		exit (EXIT_FAILURE);
	}
	else
	{
		int ret_from_fork;
		ret_from_fork = fork ();
		if (ret_from_fork == 0)  // child process
		{
		//	close (1);
			dup2 (pipe_fd[1], 1);
			execlp ("cat", "cat", "dup.c", NULL);
		}
		else
		{
		//	close (0);
			dup2 (pipe_fd[0], 0);
			close (pipe_fd[1]);
			execlp ("grep", "grep", "include", NULL);
		}
	}
	return 0;
}
