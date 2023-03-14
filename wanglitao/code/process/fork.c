
/************************************************
*      Filename: fork.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-03-06 16:01:28
* Last Modified: 2019-03-06 17:41:39
*************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (void)
{
	int ret_from_fork;

	printf ("hello\n");

	ret_from_fork = fork ();
	if (ret_from_fork == 0)
	{
		printf ("child process...\n");
		printf ("ret_from_fork = %d\n", ret_from_fork);
		exit (0);
	}
	else if (ret_from_fork > 0)
	{
		printf ("father process...\n");
		printf ("ret_from_fork = %d\n", ret_from_fork);
		return 0;
	}
	else if (ret_from_fork == -1)
	{
		perror ("fork");
		exit (-1);
	}

	printf ("world\n");
	return 0;
}
