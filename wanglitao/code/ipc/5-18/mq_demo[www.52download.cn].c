/************************************************
*      Filename: mq_demo.c
*        Author: litao.wang
*    Bug Report: 3284757626@qq.com
*   Description: 
*        Create: 2019-07-13 22:21:00
* Last Modified: 2019-07-21 18:27:04
*************************************************/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#define handle_error(msg) \
   do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main (void)
{
	mqd_t mq_id;
	if ((mq_id = mq_open("/posix_msg_queue", O_RDWR | O_CREAT, 0644, NULL)) == -1)
        handle_error("mq_open");

    struct mq_attr mq_attribute;
	if (mq_getattr (mq_id, &mq_attribute) == -1)
        handle_error("mq_getattr");
	printf ("mq_flags: %ld\n", mq_attribute.mq_flags);
	printf ("mq_maxmsg: %ld\n", mq_attribute.mq_maxmsg);
	printf ("mq_msgsize: %ld\n", mq_attribute.mq_msgsize);
	printf ("mq_curmsgs: %ld\n", mq_attribute.mq_curmsgs);

	int ret_from_fork;
	ret_from_fork = fork ();
	if (ret_from_fork == 0) // child process
	{
		char msg_buf[mq_attribute.mq_msgsize];
		memset (msg_buf, 0, mq_attribute.mq_msgsize);
        int count = 0;
		while (1)
		{
			if (mq_receive (mq_id, msg_buf, mq_attribute.mq_msgsize, NULL) == -1)
                handle_error("mq_receive");
			printf ("child process received msg: %s\n", msg_buf);
			sleep (1);
            if (++count % 10 == 0)
                break;
		}
	}
	else if (ret_from_fork > 0) //parent process
	{
        int count = 0;
		while (1)
		{
			if (mq_send (mq_id, "hello world", sizeof ("hello world"), 1) == -1)
                handle_error("mq_send");
			printf ("parent process: send msg to mqueue success\n");
			sleep (1);
            if (++count % 10 == 0)
                break;
		}
	}
	else
        handle_error("fork");
    
    mq_close (mq_id);
    sleep (5);

	if (mq_unlink ("/posix_msg_queue") == -1)
        handle_error("mq_unlink");
	return 0;
}
