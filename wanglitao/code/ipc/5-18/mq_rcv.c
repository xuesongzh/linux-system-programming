/************************************************
 *      Filename: mq_rcv.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-07-14 09:43:19
 * Last Modified: 2019-07-21 17:46:35
 *************************************************/
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    mqd_t mq_id;
    if ((mq_id = mq_open("/posix_msg_queue", O_RDONLY | O_CREAT, 0644, NULL)) == -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    struct mq_attr mq_attribute;
    if (mq_getattr(mq_id, &mq_attribute) == -1) {
        perror("mq_getattr");
        exit(EXIT_FAILURE);
    }

    char msg_buf[mq_attribute.mq_msgsize];
    memset(msg_buf, 0, mq_attribute.mq_msgsize);

    while (1) {
        if (mq_receive(mq_id, msg_buf, mq_attribute.mq_msgsize, NULL) == -1) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }
        printf("%s\n", msg_buf);
        sleep(1);
    }

    mq_close(mq_id);

    if (mq_unlink("/posix_msg_queue") == -1) {
        perror("mq_unlink");
        exit(EXIT_FAILURE);
    }
    return 0;
}
