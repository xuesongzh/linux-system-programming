/************************************************
*      Filename: sem_sync.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-07-01 10:39:21
* Last Modified: 2019-07-22 14:30:47
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>

#define SEM_NAME "/posix_sem_operation"

int main (void)
{
	int i = 0;
	int j = 0;
	int ret_fork;
	int sem_val = 0;
    sem_t *sem;
	sem = sem_open (SEM_NAME, O_CREAT, 0666, 1);

	ret_fork = fork ();
	if (ret_fork == -1)
	{
		perror ("fork");
		sem_close (sem);
		sem_unlink (SEM_NAME);
		exit (EXIT_FAILURE);
	}
	if (ret_fork == 0)
	{
		while (i++ < 10)
		{
		//	sem_trywait (sem);
            sem_wait (sem);
			sem_getvalue (sem, &sem_val);
			printf ("child process: sem value = %d\n", sem_val);
			sleep (1);
		}
        exit (EXIT_SUCCESS);
	}
	else if (ret_fork > 0)
	{
		while (j++ < 10)
		{
			sem_post (sem);
			sem_getvalue (sem, &sem_val);
			printf ("parent process: sem value = %d\n", sem_val);
			sleep (2);
		}
	}

	sem_close (sem);
	sem_unlink (SEM_NAME);
	return 0;
}
