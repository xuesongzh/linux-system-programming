/************************************************
 *      Filename: client1.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-06-14 06:36:55
 * Last Modified: 2019-07-18 18:27:45
 *************************************************/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_SERVER "fifo_server"
#define FIFO_CLIENT_1 "fifo_client1"

int main(void) {
    mkfifo(FIFO_SERVER, 0644);
    mkfifo(FIFO_CLIENT_1, 0644);
    int ret_from_fork;
    ret_from_fork = fork();
    if (ret_from_fork == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (ret_from_fork == 0)  // child process 1: write
    {
        int fd_fifo_write;
        fd_fifo_write = open(FIFO_SERVER, O_WRONLY);
        char buf[100];
        while (1) {
            memset(buf, 0, 100);
            buf[0] = '1';
            scanf("%s", buf + 1);
            write(fd_fifo_write, buf, strlen(buf) + 1);
        }
        _exit(EXIT_SUCCESS);
    } else  // parent process: read
    {
        int fd_fifo_read;
        fd_fifo_read = open(FIFO_CLIENT_1, O_RDONLY);
        char buf[100];
        while (1) {
            memset(buf, 0, 100);
            if (read(fd_fifo_read, buf, 100) > 0) {
                printf("client%c: %s\n", buf[0], buf + 1);
            }
        }
        exit(EXIT_SUCCESS);
    }
    return 0;
}
