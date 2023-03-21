/************************************************
 *      Filename: process.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-06-14 06:36:55
 * Last Modified: 2019-07-18 15:45:27
 *************************************************/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_SERVER "fifo_log_server"

int main(void) {
    mkfifo(FIFO_SERVER, 0644);
    int fifo_fd;
    fifo_fd = open(FIFO_SERVER, O_WRONLY);
    char buf[100];
    while (1) {
        memset(buf, 0, 100);
        sprintf(buf, "process %d: log----\n", getpid());
        write(fifo_fd, buf, strlen(buf));
        sleep(5);
    }
    return 0;
}
