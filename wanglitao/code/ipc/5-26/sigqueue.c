/************************************************
 * Copyright(C) zhaixue.cc All rights reserved
 *
 *      Filename: sigqueue.c
 *        Author: litao.wang
 *        E-mail: 3284757626@qq.com
 *   Description:
 *        Create: 2019-07-24 10:38:49
 * Last Modified: 2019-07-24 10:55:50
 ************************************************/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    union sigval val;
    val.sival_int = 10;
    pid_t pid = atoi(argv[1]);
    if (sigqueue(pid, SIGHUP, val) == -1) {
        perror("sigqueue");
        exit(EXIT_FAILURE);
    }
    printf("current pid:%d\n", getpid());
    return 0;
}
