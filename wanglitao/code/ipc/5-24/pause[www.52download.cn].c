/************************************************
*      Filename: pause.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-08 22:43:57
* Last Modified: 2019-07-23 13:24:43
*************************************************/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler (int unused)
{
	printf ("catch a signal SIGINT\n");
}

int main (void)
{
	signal (SIGINT, signal_handler);
	pause();
	printf ("main exit...\n");
	return 0;
}
