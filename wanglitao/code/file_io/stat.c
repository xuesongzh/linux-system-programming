
/************************************************
*      Filename: stat.c
*        Author: litao.wang
*   Description: 
*        Create: 2018-11-22 11:24:24
* Last Modified: 2018-11-22 14:14:32
*************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main (int argc, char *argv[])
{
	struct stat buf;
	if (stat (argv[1], &buf) < 0)
	{
		perror ("stat");
		return -1;
	}
	printf ("size: %ld\n", buf.st_size);
	printf ("mode: %o\n", buf.st_mode);
	printf ("inode: %ld\n", buf.st_ino);
	printf ("links: %u\n", buf.st_nlink);
	printf ("uid: %u\n", buf.st_uid);
	printf ("gid: %u\n", buf.st_gid);
	printf ("blksize: %ld\n", buf.st_blksize);
	printf ("blocks: %ld\n", buf.st_blocks);
	printf ("atime: %s", ctime (&buf.st_atime));
	printf ("mtime: %s", ctime (&buf.st_mtime));
	printf ("ctime: %s", ctime (&buf.st_ctime));
	return 0;
}
