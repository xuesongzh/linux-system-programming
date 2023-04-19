/************************************************
 *      Filename: lockf.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-06-04 22:02:28
 * Last Modified: 2019-07-23 10:30:21
 *************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    int fd, ret;
    int pid;
    fd = open("tmp.txt", O_RDWR | O_CREAT, 0666);
    ret = flock(fd, LOCK_EX);
    printf("flock return ret:%d\n", ret);
    ret = lockf(fd, F_LOCK, 0);
    printf("lockf return ret:%d\n", ret);
    sleep(30);
    return 0;
}
