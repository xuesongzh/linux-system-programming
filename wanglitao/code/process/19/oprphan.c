
/************************************************
 *      Filename: oprphan.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-03-15 17:00:42
 * Last Modified: 2019-03-15 18:03:01
 *************************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        printf("child process run pid:%d ppid:%d\n", getpid(), getppid());
        printf("child process sleep 5 seconds\n");
        sleep(5);
        printf("child process wake pid:%d ppid:%d\n", getpid(), getppid());
        printf("child process exit\n");
        exit(0);
    } else {
        printf("father process run pid:%d ppid:%d\n", getpid(), getppid());
        printf("father process sleep 1 seconds\n");
        sleep(1);
        printf("father process exited.\n");
    }
    return 0;
}
