/************************************************
*      Filename: signal.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-14 15:23:40
* Last Modified: 2019-07-23 14:59:45
*************************************************/
#include <signal.h>
#include <unistd.h>
#include <stdio.h>


void handler (int signo)
{
	switch (signo)
	{
		case 1:
			printf ("get a SIGUP signal: %d\n", signo);
			break;
		case 2:
			printf ("get a SIGINT signal: %d\n", signo);
			break;
		case 3:
			printf ("get a SIGQUIT signal: %d\n", signo);
			break;
	}
}


int main (void)
{
	signal (SIGHUP, handler);
	signal (SIGINT, handler);
	signal (SIGQUIT, handler);

	pause ();
	//while (1);

	return 0;
}

// run:  kill -HUP pid
