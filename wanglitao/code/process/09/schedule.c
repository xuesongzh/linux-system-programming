
/************************************************
*      Filename: schedule.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-03-13 13:00:40
* Last Modified: 2019-03-13 14:33:21
*************************************************/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	int ret_from_fork;
	int child_count = 0;
	int father_count = 0;
	int i;

	ret_from_fork = fork ();
	if (ret_from_fork > 0)
	{
		while (1)
		{
			for (i = 0; i < 10000000; i++);
			printf ("father process! %d\n",father_count++);
		//	sleep (5);
		}
		exit (0);
	}
	else if (ret_from_fork == 0)
	{
		while (1)
		{
			for (i = 0; i < 20000000; i++);
			printf ("child process! %d\n",child_count++);
		//	sleep (1);
		}
		exit (0);
	}
	else
	{
		perror ("fork");
		return -1;
	}
	return 0;
}
