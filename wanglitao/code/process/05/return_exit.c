
/************************************************
*      Filename: main.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-03-11 22:18:56
* Last Modified: 2019-03-13 09:03:17
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int f3 (void)
{
	printf("%s\n", __func__);
	//abort ();
	//exit (0);
	return 0;
}
void f2 (void)
{
	f3 ();
	printf ("%s\n", __func__);
}

void f1 (void)
{
	f2 ();
//	while (1);
	printf ("%s\n", __func__);
}

int main (void)
{
	f1 ();
	printf ("%s\n", __func__);
	//exit (0);
	//_exit (0);
	return 0;
}
