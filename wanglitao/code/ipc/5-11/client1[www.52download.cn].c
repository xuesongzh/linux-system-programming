/************************************************
*      Filename: client1.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-07-14 15:52:50
* Last Modified: 2019-07-20 09:02:26
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define handle_error(msg) \
    {perror(msg);exit(EXIT_FAILURE);}

#define MSG_TYPE1 1
#define MSG_TYPE2 2

struct msgbuf
{
	long mtype;
	char mtext[80];
};

int main (int argc, char *argv[])
{
//	key_t key = ftok (".", 511);
	key_t key = 511;
	int msg_id = msgget (key, IPC_CREAT | 0666);
	struct msgbuf msg1, msg2;

	int ret_from_fork;
	ret_from_fork = fork ();
	if (ret_from_fork == -1)
        handle_error("fork")
	else if (ret_from_fork == 0)
	{
		while (1)
		{
			gets (msg1.mtext);
			msg1.mtype = MSG_TYPE1;
			msgsnd (msg_id, &msg1, 80, 0);
		}
	}
	else
	{
		while (1)
		{
			memset (&msg2, 0, sizeof(msg2));
			if (msgrcv (msg_id, (void *)&msg2, \
                        sizeof(msg2.mtext), MSG_TYPE2, 0) == -1)
			    handle_error("msgrcv");
            printf ("client2: %s\n", msg2.mtext);
		}
	}
	msgctl (msg_id, IPC_RMID, NULL);
	return 0;
}
