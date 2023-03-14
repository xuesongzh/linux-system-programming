
/************************************************
*      Filename: setuid.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-03-14 09:15:12
* Last Modified: 2019-03-14 10:25:44
*************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main (void)
{
	int ret_from_fork;

	ret_from_fork = fork ();
	if (ret_from_fork == 0)
	{
		printf ("child process...\n");
		printf ("uid:%d\n", getuid ());
		setuid (1000);
		printf ("uid:%d\n", getuid ());
	//	while (1);
		exit (0);
	}
	
	printf ("father process...\n");
	
	return 0;
}
