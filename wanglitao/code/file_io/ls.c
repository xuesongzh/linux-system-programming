
/************************************************
*      Filename: ls.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2018-11-23 18:20:35
* Last Modified: 2018-11-23 19:00:12
*************************************************/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main (void)
{
	DIR *dir_ptr;
	struct dirent *entry_ptr;
	int count = 0;

	dir_ptr = opendir (".");
	while ((entry_ptr = readdir (dir_ptr)) != NULL)
	{
		if (++count % 10 == 0 )
			printf ("\n");
		printf ("%6s", entry_ptr->d_name);
	}
	printf ("\n");
	return 0;
}
