/************************************************
*      Filename: sem_post.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-07-03 12:44:35
* Last Modified: 2019-07-22 14:38:25
*************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main (void)
{
	char *name = "/posix_sem";
	unsigned int sem_value = 4;
	sem_t *sem = sem_open (name, O_RDWR | O_CREAT, 0777, sem_value);
	if (sem == SEM_FAILED)
	{
		perror ("sem_open");
		exit (EXIT_FAILURE);
	}
	printf ("sem_open %s success\n", name);

	while (1)
	{
		if (sem_post (sem) == -1)
		{
			perror ("sem_post");
			return -1;
		}
		if (sem_getvalue (sem, &sem_value) != -1)
			printf ("post process: sem value=%d\n", sem_value);
		sleep (5);
	}

	sleep (10);
    
	if (sem_unlink (name) != -1)
		printf ("sem_unlink %s success\n", name);

	return 0;
}
