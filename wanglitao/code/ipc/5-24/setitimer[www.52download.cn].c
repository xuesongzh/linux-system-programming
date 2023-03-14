/************************************************
*      Filename: setimer.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-08 22:49:05
* Last Modified: 2019-07-23 15:08:33
*************************************************/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>


void signal_handler (int signum)
{
	switch (signum)
	{
		case SIGALRM:
			printf ("catch a signal: SIGALRM\n");
			break;
		case SIGVTALRM:
			printf ("catch a signal: SIGVTALRM\n");
			break;
	}
	return;
}

int main (void)
{
	struct itimerval value,old_value, value2;
	printf ("process id: %d\n", getpid());
	signal (SIGALRM, signal_handler);
	signal (SIGVTALRM, signal_handler);

	value.it_value.tv_sec = 5;
	value.it_value.tv_usec = 0;
	value.it_interval.tv_sec = 1;
	value.it_interval.tv_usec = 0;
	setitimer (ITIMER_REAL, &value, &old_value);

	value2.it_value.tv_sec = 10;
	value2.it_value.tv_usec = 0;
	value2.it_interval.tv_sec = 1;
	value2.it_interval.tv_usec = 0;
	setitimer (ITIMER_VIRTUAL, &value2, &old_value);
	while (1)
    {
       // for(;;);
       sleep (5);
    }
	return 0;
}
