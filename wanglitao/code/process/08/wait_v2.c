
/************************************************
*      Filename: wait_v2.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: get wait return staus
*        Create: 2019-03-13 12:00:40
* Last Modified: 2019-03-13 13:33:32
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
	int i;
	ret_from_fork = fork ();
	if (ret_from_fork > 0)
	{
			int wait_return_pid;
			int status = 0;
			printf ("father process(pid:%d) start\n", getpid ());
			wait_return_pid = wait (&status);
			if (wait_return_pid == -1)
				perror ("wait");
			if (WIFEXITED (status))
				printf ("wait child process(pid:%d)return succuss, exit value:%d\n",\
						wait_return_pid, WEXITSTATUS (status));
			printf ("father process(pid:%d) exit\n",getpid ());
			exit (0);
	}
	else if (ret_from_fork == 0)
	{
		child_process ();
	}
	else
	{
		perror ("fork");
		return -1;
	}
	return 0;
}
