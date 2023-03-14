
/************************************************
*      Filename: ls_v2.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: ls dir1 dir2
*        Create: 2018-11-23 18:20:35
* Last Modified: 2018-11-23 19:40:57
*************************************************/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int do_ls (char pathname[]);

int main (int argc, char *argv[])
{
	if (argc == 1)
		do_ls (".");
	else
		while (--argc)
		{
			printf ("%s:\n", *++argv);
			do_ls (*argv);
		}
	return 0;
}

int do_ls (char pathname[])
{
	DIR *dir_ptr;
	struct dirent *entry_ptr;
	int count = 0;

	dir_ptr = opendir (pathname);
	while ((entry_ptr = readdir (dir_ptr)) != NULL)
	{
		if (++count % 10 == 0 )
			printf ("\n");
		printf ("%s  ", entry_ptr->d_name);
	}
	printf ("\n");

	closedir (dir_ptr);
	return 0;
}
