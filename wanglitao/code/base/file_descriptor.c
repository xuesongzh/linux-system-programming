
/************************************************
*      Filename: file_descriptor.c
*        Author: litao.wang
*   Description: 
*        Create: 2018-10-05 17:34:10
* Last Modified: 2018-10-05 17:44:27
*************************************************/
#include <unistd.h>
#include <string.h>
int main (void)
{
	char buf[20] = {0};
	read (0, buf, 15);
	write (1, buf, strlen(buf));
	return 0;
}
