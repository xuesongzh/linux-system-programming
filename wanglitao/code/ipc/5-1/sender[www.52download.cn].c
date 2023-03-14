#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	printf ("write process pid: %d\n", getpid ());
 	char buf[64] = { 0 };
  	int n = 0;
  	while (1) 
  	{
    	if ((n = read (STDIN_FILENO, buf, 64)) > 0) 
		{
      		int fd = open ("data.txt", O_WRONLY|O_CREAT, 0664);
      		if (fd < 0) 
	  		{
        		perror ("open");
        		continue;
      		}   
	  	buf[n] = '\0';
      	write (fd, buf, n + 1); 
      	close (fd);
    	}   
  	}
  	return 0;
}
