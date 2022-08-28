#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <errno.h>
#include <signal.h>
#include <poll.h>

int main(void)
{
        char buf[200] = {0};
        struct pollfd fds[2] = {0};
        int ret = -1, mouse_fd = -1; 

        mouse_fd = open("/dev/input/mouse1", O_RDONLY); //打开鼠标
        if(mouse_fd < 0) {
                perror("open /dev/input/mouse1 is fail");
                exit(-1);
        }

        /* 设置需要多路监听的fd */
        fds[0].fd = 0; //标准IO
        fds[0].events = POLLIN; //设置希望的事件，POLLIN：输入事件
        fds[1].fd = mouse_fd; //鼠标
        fds[1].events = POLLIN; //设置希望的事件，POLLIN：输入事件       

        while(1)
        {
                /* fds：struct pollfd结构数组，2：需要多路监听的数量，3000：超时时间 */
        lab0:    ret = poll(fds, 2, 3000);
                if(ret<0 && EINTR==errno) //重启被信号中断了的poll调用
                {
                        printf("interrupt poll\n");
                        goto lab0;
                }
                else if(ret < 0) {
                        perror("poll is fail");
                        exit(-1);
                }
                else if(0 == ret) printf("time out\n"); //超时时间到
                else if(ret > 0)
                {
                         /* 如果响应事件revents等于希望的时间events，说明该描述符动作了，可以执行相应操作了 */
                        if(fds[0].events == fds[0].revents)  //判断键盘输入
                        {
                                bzero(buf, sizeof(buf));
                                ret = read(fds[0].fd, buf, sizeof(buf));
                                if(ret > 0) write(1, buf, strlen(buf));
                        }
                        if(fds[1].events == fds[1].revents)//判断鼠标输入
                        {
                                bzero(buf, sizeof(buf));
                                ret = read(fds[1].fd, buf, sizeof(buf));
                                if(ret > 0) write(1, buf, strlen(buf));
                        }
                }
        }
        return 0;
}
