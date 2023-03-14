
/************************************************
*      Filename: ls_v4.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: ls -l 
*        Create: 2018-11-23 18:20:35
* Last Modified: 2018-11-24 14:58:47
*************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <libgen.h>

int do_ls (char pathname[]);
int print_ll (char filename[]);

int c_flag;
int l_flag;
int dir_count;

void check_param (int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (strcmp (argv[i], "-c") == 0)
			c_flag = 1;
		else if (strcmp (argv[i], "-l") == 0)
			l_flag = 1;
		else
			dir_count++;

	}
}

int main (int argc, char *argv[])
{
	check_param (argc, argv);

	if (argc == 1 || dir_count == 0)
		do_ls (".");
	else
		while (--argc)
		{
			if (strcmp (*++argv, "-c") == 0)
				continue;
			if (strcmp (*argv, "-l") == 0)
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
		if (l_flag)
		{
			char tmp[128];
			strcpy (tmp, pathname);
			strcat (tmp, entry_ptr->d_name);
			print_ll (tmp);
		}
		else
			printf ("%s  ", entry_ptr->d_name);
	}
	printf ("\n");

	closedir (dir_ptr);
	return 0;
}

char *change_mode_to_string(mode_t mode)
{
	static char mode_string[10];
	strcpy (mode_string, "----------");
	if (S_ISDIR(mode)) mode_string[0] = 'd';
	if (S_ISCHR(mode)) mode_string[0] = 'c';
	if (S_ISBLK(mode)) mode_string[0] = 'b';
	if (S_ISLNK(mode)) mode_string[0] = 'l';
	if (S_ISFIFO(mode)) mode_string[0] = 'f';
	if (S_ISSOCK(mode)) mode_string[0] = 's';

	if (mode & S_IRUSR) mode_string[1] = 'r';
	if (mode & S_IWUSR) mode_string[2] = 'w';
	if (mode & S_IXUSR) mode_string[3] = 'x';
	if (mode & S_IRGRP) mode_string[4] = 'r';
	if (mode & S_IWGRP) mode_string[5] = 'w';
	if (mode & S_IXGRP) mode_string[6] = 'x';
	if (mode & S_IROTH) mode_string[7] = 'r';
	if (mode & S_IWOTH) mode_string[8] = 'w';
	if (mode & S_IXOTH) mode_string[9] = 'x';

	return mode_string;
}

char * find_user_name_by_uid (uid_t uid)
{
	struct passwd *passwd_ptr;

	passwd_ptr = getpwuid (uid);
	if (passwd_ptr == NULL)
	{
		static char uid_string[10];
		sprintf (uid_string, "%d", uid);
		return uid_string;
	}
	return passwd_ptr->pw_name;
}

char *find_group_name_by_gid (gid_t gid)
{
	struct group *group_ptr;

	group_ptr = getgrgid (gid);
	if (group_ptr == NULL)
	{
		static char gid_string[10];
		sprintf (gid_string, "%d", gid);
		return gid_string;
	}
	return group_ptr->gr_name;
}
int print_ll (char filename[])
{
	struct stat buf;
	if (stat (filename, &buf) < 0)
	{
		perror ("stat");
		return -1;
	}
	printf ("%-12s", basename(filename));
	printf ("%s ", change_mode_to_string (buf.st_mode));
	printf ("%u ", buf.st_nlink);
	printf ("%s ", find_user_name_by_uid (buf.st_uid));
	printf ("%s ", find_group_name_by_gid (buf.st_gid));
	printf ("%ld ", buf.st_size);
	printf ("%s ", ctime (&buf.st_atime));
	return 0;
}
