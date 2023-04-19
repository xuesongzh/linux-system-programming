/************************************************
 *      Filename: wrire_shm_sem.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-07-03 22:07:06
 * Last Modified: 2019-07-22 17:52:05
 *************************************************/
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHM_NAME "/memmap"
#define SEM_NAME "/memmap_sem"

int main(void) {
    int shm_fd;
    sem_t *sem;
    shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0666);
    sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);
    if (shm_fd < 0 || sem == SEM_FAILED) {
        perror("open");
        return -1;
    }
    ftruncate(shm_fd, 8192);
    struct stat filestat;
    fstat(shm_fd, &filestat);
    printf("st_size: %ld\n", filestat.st_size);
    char *shm_ptr;
    shm_ptr = (char *)mmap(NULL, filestat.st_size,
                           PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    close(shm_fd);

    char msg[] = "hello world";
    memmove(shm_ptr, msg, sizeof(msg));
    printf("pid %d: %s\n", getpid(), shm_ptr);

    sem_post(sem);
    sem_close(sem);
    sleep(5);
    munmap(shm_ptr, 8192);

    return 0;
}
