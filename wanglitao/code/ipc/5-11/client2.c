/************************************************
 *      Filename: client2.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-07-14 16:03:42
 * Last Modified: 2019-07-19 17:37:54
 *************************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#define handle_error(msg)   \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    }

#define MSG_TYPE1 1
#define MSG_TYPE2 2

struct msgbuf {
    long mtype;
    char mtext[80];
};

int main(void) {
    //	key_t key = ftok (".", 511);
    key_t key = 511;
    int msg_id = msgget(key, IPC_CREAT | 0666);
    struct msgbuf msg1, msg2;

    int ret_from_fork;
    ret_from_fork = fork();
    if (ret_from_fork == -1) {
        handle_error("fork");
    } else if (ret_from_fork == 0) {
        while (1) {
            gets(msg2.mtext);
            msg2.mtype = MSG_TYPE2;
            msgsnd(msg_id, &msg2, 80, 0);
        }
    } else {
        while (1) {
            memset(&msg1, 0, sizeof(msg1));
            if (msgrcv(msg_id, (void *)&msg1,
                       sizeof(msg1.mtext), MSG_TYPE1, 0) == -1)
                handle_error("msgrcv");
            printf("client1: %s\n", msg1.mtext);
        }
    }
    return 0;
}
