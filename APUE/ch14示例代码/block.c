#include "apue.h"
#include <fcntl.h>
int main(void)
{
        char buf[100] = {0};  
        int fd = -1, ret = -1; 

          /* 打开鼠标文件 */  
        fd = open("/dev/input/mouse1", O_RDONLY);
        if(fd < 0)
        {    
                perror("open /dev/input/mouse1 is fail");
                exit(-1);
        }   
    
        /* 由于读键盘和读鼠标默认都是阻塞的操作，所以它们会相互阻塞 */
        while(1)
        {   
                /* 先读键盘 */
                bzero(buf, sizeof(buf));
                ret = read(0, buf, sizeof(buf));
                if(ret > 0) write(1, buf, strlen(buf));
    
                /* 后读鼠标 */
                bzero(buf, sizeof(buf));
                ret = read(fd, buf, sizeof(buf));
                if(ret > 0) write(1, buf, strlen(buf));
        }   

        return 0;
}
