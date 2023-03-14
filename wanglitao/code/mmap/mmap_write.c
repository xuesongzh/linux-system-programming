#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
	int fd;
	int i;
	char *p_map;
	fd = open (argv[1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	write (fd, "", 1);
	p_map = (char *) mmap (NULL, 20, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (p_map == MAP_FAILED)
	{
		perror ("mmap");
		return -1;
	}
	close (fd);
	if (fd == -1)
	{
		perror ("close");
		return -1;
	}
	memcpy (p_map, "hello world!\n", 14);
	sleep (5);
	if (munmap (p_map, 20) == -1)
	{
		perror ("munmap");
		return -1;
	}
	return 0;
}
