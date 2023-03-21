/************************************************
 *      Filename: dup.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-06-21 09:29:14
 * Last Modified: 2019-07-17 17:14:53
 *************************************************/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main1(void) {
    int fd, new_fd;
    fd = open("write.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    new_fd = dup(fd);
    printf("fd = %d\nnew_fd = %d\n", fd, new_fd);
    write(fd, "hello", strlen("hello"));
    close(fd);
    write(new_fd, "world", strlen("world"));
    close(new_fd);
    return 0;
}

// 复制fd
int main(void) {
    int new_fd;
    new_fd = dup(1);
    write(1, "hello", strlen("hello"));
    write(new_fd, "world\n", strlen("world\n"));
    close(new_fd);
    return 0;
}
