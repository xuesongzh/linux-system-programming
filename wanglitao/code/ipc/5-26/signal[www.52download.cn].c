/************************************************
*      Filename: signal.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-14 15:23:40
* Last Modified: 2019-07-24 11:14:35
*************************************************/
#include <signal.h>
#include <unistd.h>
#include <stdio.h>


void handler (int signo)
{
	switch (signo)
	{
		case SIGHUP:
			printf ("get a SIGHUP signal: %d\n", signo);
			break;
		case SIGINT:
			printf ("get a SIGINT signal: %d\n", signo);
			break;
		case SIGQUIT:
			printf ("get a SIGQUIT signal: %d\n", signo);
			break;
        case SIGUSR1:
            printf ("get a SIGUSR1 signal: %d\n", signo);
            break;
        default:
            printf ("unknow signal\n");
	}
    for (int i = 0; i < 10000; i++)   //delay 
    {
        for (int j = 0; j < 1000; j++)
            ;
    }
    printf ("handler exit with signo: %d\n", signo);
}


int main (void)
{
	signal (SIGHUP, handler);
	signal (SIGINT, handler);
	signal (SIGQUIT, handler);
	signal (SIGUSR1, handler);

	while (1);
	return 0;
}
//test 1:
// run:  kill -HUP  22380
// run:  kill -HUP  22380
// run:  kill -HUP  22380
// run:  kill -HUP  22380
// run:  kill -HUP  22380
//test 2:
// run:  kill -HUP  22380
// run:  kill -INT  22380
// run:  kill -QUIT  22380
// run:  kill -USR1  22380
// run:  kill -HUP  22380
