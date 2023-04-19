/************************************************
 *      Filename: sem_wait.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-07-01 22:03:27
 * Last Modified: 2019-07-22 14:37:31
 *************************************************/
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    char *name = "/posix_sem";
    unsigned int sem_value = 4;
    sem_t *sem = sem_open(name, O_RDWR | O_CREAT, 0777, sem_value);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    printf("sem_open %s success\n", name);

    while (1) {
        if (sem_wait(sem) == -1) {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
        if (sem_getvalue(sem, &sem_value) != -1)
            printf("wait process: sem value=%d\n", sem_value);
        sleep(1);
    }

    sleep(10);
    sem_close(sem);
    if (sem_unlink(name) != -1)
        printf("sem_unlink %s success\n", name);

    return 0;
}
