/************************************************
*      Filename: shm_read.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-07-14 16:46:40
* Last Modified: 2019-07-20 11:43:36
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main (int argc, char *argv[])
{
	key_t key = ftok ("./", 513);
	int shm_id = shmget (key, 4096, 0666);

	char *shm_p = shmat (shm_id, NULL, 0);
	printf ("from SHM:%s", shm_p);

	shmdt (shm_p);

	return 0;
}
