
/************************************************
*      Filename: atexit.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-03-12 16:37:08
* Last Modified: 2019-03-13 08:21:53
*************************************************/
#include <stdio.h>
#include <stdlib.h>

static void exit_process1 (void)
{
	printf ("exit process func1\n");
}

static void exit_process2 (void)
{
	printf ("exit process func2\n");
}

static void on_exit_process (int exit_status, void *arg)
{
	printf ("on_exit_process called:status = %d, args=%d\n", exit_status, (int)arg);
}

int main (void)
{
	if (atexit (exit_process1) != 0)
		perror ("atexit 1");
	if (atexit (exit_process2) != 0)
		perror ("atexit 2");
	if (on_exit (on_exit_process, (void *) 20) != 0)
		perror ("on_exit");
	exit (5);
//	return 0;
}
