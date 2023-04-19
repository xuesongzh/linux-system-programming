/************************************************
 *      Filename: sem_demo.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-07-01 22:03:27
 * Last Modified: 2019-07-22 14:31:26
 *************************************************/
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    unsigned int sem_value = 4;
    sem_t *sem = sem_open("posix_sem", O_RDWR | O_CREAT | O_EXCL, 0777, sem_value);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    if (sem_getvalue(sem, &sem_value) != -1)
        printf("the sem value: %d\n", sem_value);
    // P -1
    sem_wait(sem);
    sem_wait(sem);
    sem_wait(sem);
    sem_wait(sem);
    // sem_wait (sem);阻塞
    sem_trywait(sem);
    if (sem_getvalue(sem, &sem_value) != -1)
        printf("the sem value: %d\n", sem_value);
    // V +1
    sem_post(sem);
    sem_post(sem);
    sem_post(sem);
    sem_post(sem);
    sem_post(sem);
    sem_post(sem);
    if (sem_getvalue(sem, &sem_value) != -1)
        printf("the sem value: %d\n", sem_value);

    if (sem_close(sem) != -1)
        printf("sem close posix_sem success\n");

    printf("wait for sem_unlink, 10s\n");
    sleep(10);

    if (sem_unlink("posix_sem") != -1)
        printf("sem_unlink posix_sem success\n");

    return 0;
}
