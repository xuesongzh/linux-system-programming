/************************************************
*      Filename: kill.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-21 14:43:11
* Last Modified: 2019-07-23 14:55:35
*************************************************/
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main (void)
{
	while (1)
	{
		kill (7118, SIGHUP);
		sleep (2);
	}
	return 0;
}
