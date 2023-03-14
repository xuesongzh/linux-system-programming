/************************************************
*      Filename: shm_read.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-07-03 22:17:57
* Last Modified: 2019-07-22 17:03:03
*************************************************/
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define SHM_NAME "/shm"

int main (void)
{
	int shm_fd;
	shm_fd = shm_open (SHM_NAME, O_RDWR | O_CREAT, 0);
	if (shm_fd < 0)
	{
		perror ("shm_open");
		return -1;
	}
	ftruncate (shm_fd, 8192);
	struct stat filestat;
	fstat (shm_fd, &filestat);
    printf ("st_size: %ld\n", filestat.st_size);
	char *shm_ptr;
	shm_ptr = (char*)mmap (NULL, filestat.st_size, \
            PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
	close (shm_fd);
	printf ("pid %d: %s\n", getpid(), shm_ptr);
    munmap (shm_ptr, filestat.st_size);
    shm_unlink (SHM_NAME);
	return 0;
}
