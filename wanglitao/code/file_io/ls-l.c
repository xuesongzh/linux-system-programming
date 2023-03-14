
/************************************************
*      Filename: ls-l.c
*        Author: litao.wang
*   Description: shell command;ls -l
*        Create: 2018-11-22 11:24:24
* Last Modified: 2018-11-24 13:10:40
*************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

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

int main (int argc, char *argv[])
{
	struct stat buf;
	if (stat (argv[1], &buf) < 0)
	{
		perror ("stat");
		return -1;
	}
	printf ("%s ", change_mode_to_string (buf.st_mode));
	printf ("%u ", buf.st_nlink);
	printf ("%s ", find_user_name_by_uid (buf.st_uid));
	printf ("%s ", find_group_name_by_gid (buf.st_gid));
	printf ("%ld ", buf.st_size);
	printf ("%s ", ctime (&buf.st_atime));
	return 0;
}
