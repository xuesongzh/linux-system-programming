
/************************************************
*      Filename: ls_v3.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: ls -c 
*        Create: 2018-11-23 18:20:35
* Last Modified: 2018-11-24 11:30:06
*************************************************/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
int do_ls (char pathname[]);

int c_flag;

int main (int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (strcmp (argv[i], "-c") == 0)
			c_flag = 1;
	}
	if (argc == 1 || (argc == 2 && c_flag == 1))
		do_ls (".");
	else
		while (--argc)
		{
			if (strcmp (*++argv, "-c") == 0)
				continue;
			printf ("%s:\n", *argv);
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
	{
		if (dir_ptr == NULL)
		{
			perror ("opendir");
			return -1;
		}
	}
	while ((entry_ptr = readdir (dir_ptr)) != NULL)
	{
		if ((strcmp (entry_ptr->d_name, ".") && strcmp (entry_ptr->d_name, "..")) == 0)
			continue;
		if (c_flag)
			if (strcmp (entry_ptr->d_name + strlen (entry_ptr->d_name) -2, ".c"))
				continue;
		if (++count % 10 == 0 )
			printf ("\n");
		printf ("%s  ", entry_ptr->d_name);
	}
	printf ("\n");

	closedir (dir_ptr);
	return 0;
}
