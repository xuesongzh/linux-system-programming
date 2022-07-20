#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "apue.h"

int main(void)
{
        int ret = -1, fd = -1;

        fd = open("./file1", O_CREAT|O_RDWR, 0664);
        if(fd < 0){
                perror("open ./file is fail");
                exit(-1);
        }

        /* 父子进程并发的向文件写hello world*/
        ret = fork();
        if(ret == 0){ /*child */
                while(1)
                {
                        writew_lock(fd,0,SEEK_SET,0);//对整个文件加锁
                        write(fd, "hello ", 6);
                        write(fd, "world\n", 6);
                        un_lock(fd,0,SEEK_SET,0);//解锁
                }
        }        
        else if(ret > 0) /* parent */
        {
                while(1)
                {
                        writew_lock(fd,0,SEEK_SET,0);//对整个文件加锁
                        write(fd, "hello ", 6);
                        write(fd, "world\n", 6);
                        un_lock(fd,0,SEEK_SET,0);//解锁
                }
        }

        return 0;
}
