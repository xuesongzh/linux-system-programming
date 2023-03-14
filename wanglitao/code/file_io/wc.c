
/************************************************
*      Filename: wc.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2018-11-24 16:53:27
* Last Modified: 2018-11-24 18:33:50
*************************************************/
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int do_wc (char filename[]);
int foreach_dir (char dirname[]);

int main (int argc, char *argv[])
{
	foreach_dir (argv[1]);
	return 0;
}
int foreach_dir (char dirname[])
{
	DIR *dir_ptr;
	struct dirent *entry_ptr;
	dir_ptr = opendir (dirname);
	if (dir_ptr == NULL)
	{
		perror ("opendir");
		return -1;
	}

	char full_path_name[128];
	struct stat buf;
	while ((entry_ptr = readdir (dir_ptr)) != NULL)
	{
		if ((strcmp (entry_ptr->d_name, ".") && strcmp (entry_ptr->d_name, "..")) == 0)
			continue;
		strcpy (full_path_name, dirname);
		if (full_path_name[strlen (full_path_name) - 1] != '/')
			strcat (full_path_name, "/");
		strcat (full_path_name, entry_ptr->d_name);

		if (stat (full_path_name, &buf) < 0)
		{
			perror ("stat");
			return -1;
		}
		if (S_ISDIR (buf.st_mode))
			foreach_dir (full_path_name);
		else
		{
			if (strcmp (entry_ptr->d_name + strlen (entry_ptr->d_name) - 2, ".c") && \
				strcmp (entry_ptr->d_name + strlen (entry_ptr->d_name) - 2, ".h") && \
				strcmp (entry_ptr->d_name + strlen (entry_ptr->d_name) - 2, ".S"))
				continue;
			else
				do_wc (full_path_name);
		}

	}
	closedir (dir_ptr);
	return 0;
}

int do_wc (char filename[])
{
	FILE *fp;
	char ch;
	static unsigned int lines = 0;
	static unsigned int words = 0;
	static unsigned int files = 0;
	int word_flag = 0;
	fp = fopen (filename, "r");
	if (fp == NULL)
	{
		perror ("fopen");
		return -1;
	}
	while ((ch = fgetc (fp)) != EOF)
	{
		if (ch == '\n')
			lines++;
		if (ch == '\n' || ch == ' ' || ch == '\t')
		{
			word_flag = 1;
			continue;
		}
		else
		{
			if (word_flag == 1)
			{
				words++;
				word_flag = 0;
			}
		}
	}
	fclose (fp);
	printf ("%s\n", filename);
	printf ("files: %d\n", ++files);
	printf ("lines: %d\n", lines);
	printf ("words: %d\n", words);
	return 0;
}
