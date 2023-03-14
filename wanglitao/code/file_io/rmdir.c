
/************************************************
*      Filename: rmdir.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2018-11-24 14:59:17
* Last Modified: 2018-11-24 15:33:47
*************************************************/
#include <unistd.h>
int main (int argc, char *argv[])
{
	rmdir (argv[1]);
	return 0;
}
