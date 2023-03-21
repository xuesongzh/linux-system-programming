/************************************************
 *      Filename: pipe-v2.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-06-14 06:05:29
 * Last Modified: 2019-07-17 15:26:43
 *************************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define handle_error(msg)   \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    }

// 双向通信
int main(int argc, char *argv[]) {
    int pipe_fd1[2];
    int pipe_fd2[2];
    if (pipe(pipe_fd1) == -1 || pipe(pipe_fd2) == -1)
        handle_error("pipe");

    int ret_from_fork;
    ret_from_fork = fork();
    if (ret_from_fork == -1)
        handle_error("fork");
    if (ret_from_fork == 0)  // child process
    {
        char read_buf1[100] = {0};
        char write_buf1[100] = {0};
        printf("child process:");
        scanf("%s", write_buf1);
        // gets(str);
        write(pipe_fd1[1], write_buf1, strlen(write_buf1));
        close(pipe_fd1[1]);

        // sleep(5);
        read(pipe_fd2[0], read_buf1, 100);
        printf("in child process: %s\n", read_buf1);
        close(pipe_fd2[0]);
        _exit(EXIT_SUCCESS);
    }

    if (ret_from_fork > 0)  // parent process
    {
        char read_buf2[100] = {0};
        char write_buf2[100] = {0};
        read(pipe_fd1[0], read_buf2, 100);  // read data from pipe
        printf("in parent process: %s\n", read_buf2);
        close(pipe_fd1[0]);

        printf("parent process:");
        scanf("%s", write_buf2);
        write(pipe_fd2[1], write_buf2, strlen(write_buf2));
        close(pipe_fd2[1]);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
