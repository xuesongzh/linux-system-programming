/************************************************
*      Filename: mq_notify.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-07-16 17:35:55
* Last Modified: 2019-07-22 08:59:34
*************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

mqd_t mq_id;
char buff[8192];
struct sigevent sigev;

static void signal_hander (int signo)
{
	ssize_t receive_len;
	mq_notify (mq_id, &sigev);
	receive_len = mq_receive (mq_id, buff, 8192, NULL);
	if (receive_len == -1)
	{
		perror ("mq_receive");
		exit (EXIT_FAILURE);
	}
	printf ("read %ld bytes: %s\n",(long)receive_len, buff);
	return;
}

int main (void)
{
	mq_id = mq_open ("/notify_mqueue", O_RDONLY | O_CREAT, 0644, NULL);
	if (mq_id == -1)
	{
		perror ("mq_open");
		exit (EXIT_FAILURE);
	}

	signal (SIGUSR1, signal_hander);
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo  = SIGUSR1;
	mq_notify (mq_id, &sigev);

    int count = 0;
	while (1)
    {
        printf ("while loop %d\n", count++);
        sleep (1);
    }
    mq_close (mq_id);
	return 0;
}

