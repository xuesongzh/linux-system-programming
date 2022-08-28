
#include <fcntl.h>

int main(void)
{
        char buf[100] = {0};
        int fd = -1, ret = -1;

        /* 开来两个进程，父进程读鼠标，子进程读键盘 */
        ret = fork();
        if(ret == 0){
                while(1)
                {
                        /* 读键盘 */
                        bzero(buf, sizeof(buf));
                        ret = read(0, buf, sizeof(buf));
                        if(ret > 0) write(1, buf, strlen(buf));
                }
        }
        else if(ret > 0)
        {
                fd = open("/dev/input/mouse1", O_RDONLY);
                if(fd < 0)
                { 
                        perror("open /dev/input/mouse1 is fail");
                        exit(-1);
                }
                while(1)
                {
                        /* 读鼠标 */
                        bzero(buf, sizeof(buf));
                        ret = read(fd, buf, sizeof(buf));
                        if(ret > 0) write(1, buf, strlen(buf));
                }
       }
        return 0;
}
