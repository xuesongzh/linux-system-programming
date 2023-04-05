/************************************************
 *      Filename: msg_snd.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-07-14 16:03:42
 * Last Modified: 2019-07-19 11:50:15
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

int main(void) {
    //	key_t key = ftok (".", 510);
    key_t key = 12345;
    int msg_id = msgget(key, IPC_CREAT | 0666);

    struct msqid_ds info;
    if (msgctl(msg_id, IPC_STAT, &info) == -1)
        handle_error("msgctl");
    printf("uid:%d, gid:%d, cuid:%d, cgid:%d\n", info.msg_perm.uid,
           info.msg_perm.gid, info.msg_perm.cuid, info.msg_perm.cgid);
    printf("mode:%03o, cbytes:%lu, qnum:%lu, qbytes:%lu\n",
           info.msg_perm.mode & 0777, info.msg_cbytes,
           info.msg_qnum, info.msg_qbytes);

    info.msg_qbytes = 16380;
    if (msgctl(msg_id, IPC_SET, &info) == -1)
        handle_error("msgctl");
    if (msgctl(msg_id, IPC_STAT, &info) == -1)
        handle_error("msgctl");

    printf("mode:%03o, cbytes:%lu, qnum:%lu, qbytes:%lu\n",
           info.msg_perm.mode & 0777, info.msg_cbytes,
           info.msg_qnum, info.msg_qbytes);

    return 0;
}
