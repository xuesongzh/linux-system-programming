/************************************************
 *      Filename: pipe_sync.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-06-19 22:43:26
 * Last Modified: 2019-07-18 11:50:09
 *************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define handle_error(msg)   \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    }

int main(void) {
    int pipe_fd[2];
    int buf;

    setbuf(stdout, NULL);
    printf("parent process(%d) run...\n", getpid());

    if (pipe(pipe_fd) == -1)
        handle_error("pipe");

    for (int i = 0; i < 4; i++) {
        int ret_from_fork;
        ret_from_fork = fork();

        if (ret_from_fork == -1)
            handle_error("fork");
        if (ret_from_fork == 0)  // child process
        {
            if (close(pipe_fd[0]) == -1)
                handle_error("close");
            sleep(i * i);
            printf("child process(%d) closing pipe\n", getpid());
            if (close(pipe_fd[1]) == -1)
                handle_error("close");
            _exit(EXIT_SUCCESS);
        }
    }

    if (close(pipe_fd[1]) == -1)
        handle_error("close");

    if (read(pipe_fd[0], &buf, 1) != 0)
        perror("parent read can't get EOF");

    printf("parent process(%d) exited\n", getpid());

    return 0;
}
