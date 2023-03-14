/************************************************
*      Filename: alarm.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-08 22:43:57
* Last Modified: 2019-07-23 15:01:02
*************************************************/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler (int unused)
{
	printf ("catch a signal SIGALRM\n");
}

int main (void)
{
	signal (SIGALRM, signal_handler);
	alarm (5);
	pause ();
	//sleep (3);
	//alarm (3);
	printf ("main exit\n");
	return 0;
}
