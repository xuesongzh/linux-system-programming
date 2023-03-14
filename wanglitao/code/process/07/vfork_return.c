
/************************************************
*      Filename: vfork_return.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-03-13 10:11:16
* Last Modified: 2019-03-13 10:59:39
*************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main (void)
{
	int ret_from_fork;

	ret_from_fork = vfork ();
	if (ret_from_fork == -1)
	{
		perror ("vfork");
		exit (-1);
	}
	else if (ret_from_fork == 0)
	{
		printf ("child process\n");
		return 0;
		//exit (0);
	}

	printf ("father process\n");
	
	return 0;
}
