/************************************************
*      Filename: shm_write.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-07-14 16:40:47
* Last Modified: 2019-07-20 11:43:07
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
    int shm_id;
	shm_id = shmget (key, 4096, IPC_CREAT | 0666);
    printf ("shm_id: %d\n", shm_id);

	char *shm_p = shmat (shm_id, NULL, 0);
	memset (shm_p, 0 , 4096);

	fgets (shm_p, 4096, stdin);

	sleep (30);
	shmctl (shm_id, IPC_RMID, NULL);

	return 0;
}
