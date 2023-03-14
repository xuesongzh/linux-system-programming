/************************************************
*      Filename: server.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-07-14 16:03:42
* Last Modified: 2019-07-19 22:44:46
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


#define TO_SERVER_MSGTYPE 1000
#define CLIENT_NUMBER 3

struct msgbuf
{
	long mtype;
	int client_id;
	char mtext[80];
};

int main (void)
{
//	key_t key = ftok ("./", 512);
	key_t key = 512;
	int msg_id = msgget (key, IPC_CREAT | 0666);
	struct msgbuf msg;

    while (1)
	{
	    memset (&msg, 0, sizeof(msg));
		if (msgrcv (msg_id, (void *)&msg, sizeof(msg.mtext), \
					TO_SERVER_MSGTYPE, 0) == -1)
		{
			perror ("msgrcv");
			exit (EXIT_FAILURE);
		}
		else
		{
			for (int i = 1; i <= CLIENT_NUMBER; i++)
			{
				if (i == msg.client_id)
					continue;
				else
				{
					msg.mtype = i;
					msgsnd (msg_id, &msg, 80, 0);
				}
			}
		}
		printf ("server: %s\n", msg.mtext);
	}
	msgctl (msg_id, IPC_RMID, NULL);
	return 0;
}
