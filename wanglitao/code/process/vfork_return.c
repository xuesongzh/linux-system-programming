
/************************************************
*      Filename: vfork_return.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-03-11 13:22:42
* Last Modified: 2019-03-13 07:52:56
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//fork-先父进程后子进程
//vfork-先子进程后父进程
int main (void)
{
	int ret_from_fork;
	
	ret_from_fork = vfork ();

	if (ret_from_fork == -1)
	{
		perror ("fork");
		exit (-1);
	}
	else if (ret_from_fork == 0)
	{
		printf ("child process\n");
		//return 0;  //will cause core dump
		exit (0);
	}
	else if (ret_from_fork > 0)
	{
		printf ("father process\n");
		return 0;
	}
	return 0;
}
