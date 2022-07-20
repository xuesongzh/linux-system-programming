#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <errno.h>
#include <signal.h>

int main()
{
        sigset_t set; fd_set rdfds;  
        int mouse_fd = -1, ret = 0, i = 0;
        char buf[300] = {0}; 
        struct timeval tim = {0};
       
        mouse_fd = open("/dev/input/mouse1", O_RDONLY);
        if(mouse_fd < 0){
                perror("open /dev/input/mouse1 is fail");
                exit(-1);
        }

        while(1)
        {    
                /* refer to manual page of select */

                /* 设置读集合，设置操作必须放在循环内 */
                FD_ZERO(&rdfds); //清空读集合   
                FD_SET(mouse_fd, &rdfds); //将mouse_fd设置到读集合中 
                FD_SET(STDIN_FILENO, &rdfds); //将标准输入也设置到读集合中      

                /* 设置超时时间，设置必须放在循环内 */
                tim.tv_sec      = 3; //秒
                tim.tv_usec     = 0; //微秒

                /* please refer to manual page of select */
                /* int select(int nfds, fd_set *readfds, fd_set *writefds,
                              fd_set *exceptfds, struct timeval *timeout);
                */
      
        label:   ret = select(mouse_fd+1, &rdfds, NULL, NULL, &tim);
                if(ret<0 && EINTR==errno)  //重启被信号中断了的select系统调用
                {
                        printf(" interrupt select\n");
                        goto label;
                }
                else if(ret < 0){
                        perror("select fail");
                        exit(-1);
                }
                else if(ret > 0) //集合中有
                {
                        if(FD_ISSET(mouse_fd, &rdfds)) 
                        {         
                                bzero(buf, sizeof(buf)); 
                                ret = read(mouse_fd, buf, sizeof(buf));//读鼠标
                                if(ret > 0) write(1, buf, strlen(buf));
                        }
                        if(FD_ISSET(0, &rdfds)) //0是不是有响应的描述符
                        { 
                                bzero(buf, sizeof(buf));
                                ret = read(0, buf, sizeof(buf));//读键盘
                                if(ret > 0) write(1, buf, strlen(buf));
                        }
                }
                else if(0 == ret) printf("time out\n"); //超时
        }
        return 0;
}
