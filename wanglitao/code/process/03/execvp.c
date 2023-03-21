
/************************************************
*      Filename: execvp.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-03-11 00:24:53
* Last Modified: 2019-03-11 02:50:31
*************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int child_process (int argc, char *argv[])
{
	char *arglist[argc];
	int i;
	int ret_from_exec;

	printf ("mini shell:#\n");

	for (i = 0; i < argc; i++)
		arglist[i] = argv[i+1];
	arglist[i] = NULL;
	//printf ("hello\n");
	ret_from_exec = execvp (arglist[0], arglist);
	if (ret_from_exec == -1)
	{
		perror ("execvp");
		exit (-1);
	}
	printf ("world\n");
	return 0;
}

int main (int argc, char *argv[])
{
	int ret_from_fork;

	ret_from_fork = fork ();

	if (ret_from_fork > 0)
	{
		printf ("father process\n");
		exit (0);
	}
	else if (ret_from_fork == 0)
	{
		child_process (argc, argv);
		exit (0);
	}
	else if (ret_from_fork == -1)
	{
		perror ("fork");
		exit (-1);
	}
	return 0;
}
