/************************************************
*      Filename: msg_snd.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-07-14 16:03:42
* Last Modified: 2019-07-19 12:12:59
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_TYPE1 1
#define MSG_TYPE2 2

struct msgbuf
{
	long mtype;
	char mtext[80];
};

int main (void)
{
//	key_t key = ftok (".", 510);
	key_t key = 12345;
	int msg_id = msgget (key, IPC_CREAT | 0666);
	struct msgbuf msg;
	memset (&msg, 0, sizeof(msg));

	msg.mtype = MSG_TYPE2;
	strncpy (msg.mtext, "hello world\n", 80);

	if (msgsnd (msg_id, (void *)&msg,  \
                strlen (msg.mtext), 0) == -1)
	{
		perror ("msgsnd");
		exit (EXIT_FAILURE);
	}

	return 0;
}
