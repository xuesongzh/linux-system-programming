/************************************************
 *      Filename: fcntl.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-06-05 09:27:48
 * Last Modified: 2019-07-23 11:21:38
 *************************************************/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        int fd = open(argv[1], O_WRONLY | O_CREAT, 0666);
        if (fd == -1) {
            perror("open");
            exit(-1);
        }
        static struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_start = 0;
        lock.l_whence = SEEK_SET;
        lock.l_len = 0;
        lock.l_pid = getpid();

        printf("trying lock %s ...\n", argv[1]);
        int ret = fcntl(fd, F_SETLKW, &lock);
        if (ret == 0) {
            printf("lock %s succeed\n", argv[1]);
            while (1)
                ;
        }
    }
    return 0;
}
