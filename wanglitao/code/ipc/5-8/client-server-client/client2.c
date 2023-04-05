/************************************************
 *      Filename: client2.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-06-14 06:36:55
 * Last Modified: 2019-07-18 16:13:05
 *************************************************/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_SERVER "fifo_server"
#define FIFO_CLIENT_2 "fifo_client2"

int main(void) {
    mkfifo(FIFO_SERVER, 0644);
    mkfifo(FIFO_CLIENT_2, 0644);
    int ret_from_fork;
    ret_from_fork = fork();
    if (ret_from_fork == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (ret_from_fork == 0)  // child process 2: write
    {
        int fifo_fd_write;
        fifo_fd_write = open(FIFO_SERVER, O_WRONLY);
        char buf[100];
        while (1) {
            memset(buf, 0, 100);
            buf[0] = '1';
            scanf("%s", buf + 1);
            write(fifo_fd_write, buf, strlen(buf) + 1);
        }
        _exit(EXIT_SUCCESS);
    } else  // parent process: read
    {
        int fifo_fd_read;
        fifo_fd_read = open(FIFO_CLIENT_2, O_RDONLY);
        char buf[100];
        while (1) {
            memset(buf, 0, 100);
            if (read(fifo_fd_read, buf, 100) > 0)
                printf("client1: %s\n", buf);
        }
        exit(EXIT_SUCCESS);
    }
    return 0;
}
