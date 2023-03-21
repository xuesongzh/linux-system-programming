
/************************************************
*      Filename: fork_exit_buf.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-02-25 13:06:18
* Last Modified: 2019-03-13 10:00:10
*************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//exit 会刷新缓冲区
//_exit 不会刷新缓冲区
int main (void)
{
	printf ("hello world!\n");
//	fflush (stdout);
	write (1, "hahaha\n", 7);

	int ret_from_fork;
	ret_from_fork = fork ();
	if (ret_from_fork == -1)
	{
		perror ("fork");
		exit (1);
	}
	else if (ret_from_fork == 0)
	{
		_exit (0);
	}
	
	return 0;
}
