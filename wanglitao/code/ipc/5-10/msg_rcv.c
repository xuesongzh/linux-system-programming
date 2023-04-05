/************************************************
 *      Filename: msg_rcv.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-07-14 15:52:50
 * Last Modified: 2019-07-19 12:23:56
 *************************************************/
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#define MSG_TYPE1 1
#define MSG_TYPE2 2

struct msgbuf {
    long mtype;
    char mtext[80];
};

int main(int argc, char *argv[]) {
    //	key_t key = ftok (".", 510);
    key_t key = 12345;
    int msg_id = msgget(key, IPC_CREAT | 0666);

    struct msgbuf msg;
    memset(&msg, 0, sizeof(msg));
    if (msgrcv(msg_id, (void *)&msg,
               sizeof(msg.mtext), MSG_TYPE2, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
    printf("%s", msg.mtext);
    msgctl(msg_id, IPC_RMID, NULL);

    return 0;
}
