/************************************************
*      Filename: popen.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-06-20 07:17:24
* Last Modified: 2019-07-18 10:22:25
*************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define handle_error(msg) \
    {perror(msg);exit(EXIT_FAILURE);}

int popen_read (void)
{
	FILE *fp;
	char buf[1024] = {0};

	fp = popen ("cat popen.c", "r");
	if (fp == NULL)
        handle_error("popen");
	fread (buf, 1, 1024, fp);
    printf ("%s\n", buf);
	pclose (fp);
	return 0;
}

int popen_write (void)
{
	FILE *fp = NULL;
	char buf[128] = {0};
	
	fp = popen ("cat > write.log", "w");
	if (fp == NULL)
	    handle_error("popen");
	fwrite ("hello world!\n", 1, sizeof ("hello world!"), fp);
	pclose (fp);

	return 0;
}

int main (void)
{
	popen_read ();
	popen_write ();
	return 0;
}
