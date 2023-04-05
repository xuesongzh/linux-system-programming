/************************************************
 *      Filename: client3.c
 *        Author: litao.wang
 *    Bug Report: 3384757636@qq.com
 *   Description:
 *        Create: 3019-06-14 06:36:55
 * Last Modified: 2019-07-18 18:28:08
 *************************************************/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_SERVER "fifo_server"
#define FIFO_CLIENT_3 "fifo_client3"

int main(void) {
    mkfifo(FIFO_SERVER, 0644);
    mkfifo(FIFO_CLIENT_3, 0644);
    int ret_from_fork;
    ret_from_fork = fork();
    if (ret_from_fork == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (ret_from_fork == 0)  // child process 3: write
    {
        int fd_fifo_write;
        fd_fifo_write = open(FIFO_SERVER, O_WRONLY);
        char buf[100];
        while (1) {
            memset(buf, 0, 100);
            buf[0] = '3';
            scanf("%s", buf + 1);
            write(fd_fifo_write, buf, strlen(buf) + 1);
        }
        _exit(EXIT_SUCCESS);
    } else  // parent process: read
    {
        int fd_fifo_read;
        fd_fifo_read = open(FIFO_CLIENT_3, O_RDONLY);
        char buf[100];
        while (1) {
            memset(buf, 0, 100);
            if (read(fd_fifo_read, buf, 100) > 0)
                printf("client%c: %s\n", buf[0], buf + 1);
        }
        exit(EXIT_SUCCESS);
    }
    return 0;
}
