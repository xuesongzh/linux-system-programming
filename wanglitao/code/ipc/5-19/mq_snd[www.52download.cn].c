/************************************************
*      Filename: mq_snd.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-14 09:40:00
* Last Modified: 2019-07-21 19:30:32
*************************************************/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

int main (void)
{
	mqd_t mq_id;
	if ((mq_id = mq_open("/notify_mqueue", O_WRONLY | O_CREAT, 0644, NULL)) == -1)
	{
		perror ("mq_open");
		exit (EXIT_FAILURE);
	}

	while (1)
	{
		if (mq_send (mq_id, "hello world", sizeof("hello world"), 1) == -1)
		{
			perror ("mq_receive");
			exit (EXIT_FAILURE);
		}
		printf ("msg send success--------\n");
		sleep (2);
	}

	return 0;
}
