
/************************************************
*      Filename: setbuf.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2018-12-09 16:03:39
* Last Modified: 2018-12-09 21:35:47
*************************************************/
#include <stdio.h>

int main (void)
{
	char buf[BUFSIZ];

	setvbuf (stdout, buf, _IOFBF, BUFSIZ);

	printf ("BUFSIX: %d\n", BUFSIZ);
	printf ("hello world!\n");

	printf ("%s\n", buf);
//	while (1);

	return 0;
}
