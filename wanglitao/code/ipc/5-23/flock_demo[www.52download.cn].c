/************************************************
*      Filename: flock_demo.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-05 22:21:05
* Last Modified: 2019-07-23 11:13:36
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <errno.h>

int main (void)
{
	int fd, i;
	char filename[] = "data.log";
	extern int errno;
	fd = open (filename, O_WRONLY | O_CREAT, 0666);
	if (fd != -1)
	{
		printf ("open file %s success \n", filename);
		printf ("pls input a num to lock the file.\n");
		scanf ("%d", &i);
        printf ("try to lock the file...\n");
		if (flock (fd, LOCK_EX) == 0)
			printf ("lock file success\n");
		else
			printf ("lock file failed\n");
        write (fd, "hello", 5);
		printf ("input a num to Unlock the file.\n");
		scanf ("%d", &i);
		if (flock (fd, LOCK_UN) == 0)
			printf ("file unlock success\n");
		else
			printf ("file unlock failed\n");

        while (1);
	}
	else
	{
		perror ("open");
		exit (EXIT_FAILURE);
	}
	return 0;
}
