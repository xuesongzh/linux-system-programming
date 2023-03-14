/************************************************
*      Filename: sem_creat.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: semphore basic usage 
*        Create: 2019-06-22 02:07:47
* Last Modified: 2019-07-20 15:33:20
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#define handle_error(msg) \
    {perror(msg);exit(EXIT_FAILURE);}

// creat a semphore
// print and set semphore
// P/V sem value
// delete sem

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

/*
struct sembuf
{
	unsigned short sem_num;//semaphore index in array
	short sem_op;          //sepaphore operation
	short sem_flg;         //operation flags
};
*/

int main (void)
{
	int sem_id;
	key_t key;

	if ((key = ftok(".", 514))== -1)
        handle_error("ftok");

	if ((sem_id = semget (key, 3, IPC_CREAT | 0770)) == -1)
        handle_error("semget");
	printf ("sem id: %d\n", sem_id);

	// get sem value
	int sem_value;
	sem_value = semctl (sem_id, 0, GETVAL);
	printf ("sem value: %d\n", sem_value);

	// set sem value
	union semun sem_union;
	sem_union.val = 2;
	semctl (sem_id, 0, SETVAL, sem_union);
	sem_value = semctl (sem_id, 0, GETVAL);
	printf ("sem value: %d\n", sem_value);


	//sem p/v operations
	struct sembuf sops;
	sops.sem_num = 0;
	sops.sem_op = -1;// if sem value=0, blocked
	sops.sem_flg = SEM_UNDO;
	if (semop (sem_id, &sops, 1) == -1)
        handle_error("sem_op");
	sem_value = semctl (sem_id, 0, GETVAL);
	printf ("sem value: %d\n", sem_value);
	
	sleep (30);
	semctl (sem_id, 0, IPC_RMID);

	return 0;
}
