
/************************************************
*      Filename: pwd.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2018-11-24 15:34:09
* Last Modified: 2018-11-24 16:52:51
*************************************************/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main (int argc, char *argv[])
{
	char buffer[128];
	getcwd (buffer, 128);
	printf ("%s\n", buffer);
	strcat (buffer, "/");
	strcat (buffer, argv[1]);
	printf ("%s\n", buffer);
	return 0;
}
