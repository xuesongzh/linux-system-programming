#include <stdio.h>
#include <signal.h>
#include <fcntl.h>

int mouse_fd;

void signal_fun(int signo)
{
    char buf[200] = {0};
    int ret = -1;
    memset(buf, 0, sizeof(buf));
    ret = read(mouse_fd, buf, sizeof(buf));//读鼠标
    if(ret > 0) write(1, buf, strlen(buf));    
    else if(ret < 0)
    {
        perror("read is fail");
        exit(-1);
    }
}

int main(void)
{    
    
    char buf[200] = {0};
    int flag = -1, ret = -1;

    mouse_fd = open("/dev/input/mouse1", O_RDONLY); //打开鼠标字符设备文件
    if(mouse_fd < 0)
    {
        perror("open mouse1 is fail");
        exit(-1);
    }
    /* 对mouse_fd设置异步IO */
    flag = fcntl(mouse_fd, F_GETFL);
    flag |= O_ASYNC;
    fcntl(mouse_fd, F_SETFL, flag);
    fcntl(mouse_fd, F_SETOWN, getpid()); //设置当前进程获取SIGIO信号
    signal(SIGIO, signal_fun);//捕获SIGIO信号

    while(1)
    {
        memset(buf, 0, sizeof(buf));
        ret = read(0, buf, sizeof(buf));//读键盘
        if(ret > 0) write(1, buf, strlen(buf));
        else if(ret < 0)
        {
            perror("read is fail");
            exit(-1);
        }
    }
    return 0;
}
