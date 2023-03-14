
/************************************************
*      Filename: wait.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-03-13 11:00:40
* Last Modified: 2019-03-13 12:51:37
*************************************************/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int child_process (void)
{
	printf ("child process(pid:%d) start\n", getpid());
	;
	;
	printf ("child process exit\n");
	exit (100);
}
int main (void)
{
	int ret_from_fork;

	ret_from_fork = fork ();

	if (ret_from_fork > 0)
	{
			int wait_return_pid;

			printf ("father process(pid:%d) start\n", getpid());
			wait_return_pid = wait (NULL);
			if (wait_return_pid == -1)
			{
				perror ("wait");
				exit (-1);
			}
			printf ("wait child process(pid:%d) exit succuss\n ", \
					 wait_return_pid);
			exit (0);
	}
	else if (ret_from_fork == 0)
		child_process ();
	else
	{
		perror ("fork");
		exit (-1);
	}
	return 0;
}
