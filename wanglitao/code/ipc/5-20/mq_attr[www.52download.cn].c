/************************************************
* Copyright(C) zhaixue.cc All rights reserved
*
*      Filename: mq_attr.c
*        Author: litao.wang
*        E-mail: 3284757626@qq.com
*   Description: 
*        Create: 2019-07-22 10:31:04
* Last Modified: 2019-07-22 13:05:21
************************************************/
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error(msg)    \
	do{ perror(msg); exit(EXIT_FAILURE);} while (0)

int main(int argc, char *argv[])
{
    mqd_t mq_id;
    struct mq_attr attr;

    attr.mq_maxmsg  = 5;
    attr.mq_msgsize = 4096;
    attr.mq_flags   = O_NONBLOCK;
    mq_id = mq_open("/mqueue_attr", O_CREAT, S_IRUSR | S_IWUSR, &attr);
    if (mq_id == (mqd_t) -1)
        handle_error("mq_open");

    if (mq_getattr(mq_id, &attr) == -1)
        handle_error("mq_getattr");

    printf("Maximum # of messages on queue:   %ld\n", attr.mq_maxmsg);
    printf("Maximum message size:             %ld\n", attr.mq_msgsize);
    printf("Flags:             %ld\n", attr.mq_flags);

  //  attr.mq_maxmsg  = 5;
  //  attr.mq_msgsize = 4096;
    attr.mq_flags   = O_NONBLOCK;
    if (mq_setattr(mq_id, &attr, NULL) == -1)
        handle_error("mq_setattr");
    if (mq_getattr(mq_id, &attr) == -1)
        handle_error("mq_getattr");

    printf("Maximum # of messages on queue:   %ld\n", attr.mq_maxmsg);
    printf("Maximum message size:             %ld\n", attr.mq_msgsize);
    printf("Flags:             %ld\n", attr.mq_flags);

    if (mq_unlink("/mqueue_attr") == -1)
        handle_error("mq_unlink");

    exit(EXIT_SUCCESS);
}

