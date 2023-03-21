
/************************************************
 *      Filename: signal.c
 *        Author: litao.wang
 *    Bug Report: 3284757626@qq.com
 *   Description:
 *        Create: 2019-03-14 15:08:03
 * Last Modified: 2019-03-14 16:02:03
 *************************************************/
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signal_handler(int sigal_num) {
    switch (sigal_num) {
        case SIGHUP:
            printf("get signal:SIGHUP\n");
            break;
        case SIGINT:
            printf("get signal:SIGINT\n");
            break;
        case SIGQUIT:
            printf("get signal:SIGQUIT\n");
            break;
        case SIGILL:
            printf("get signal:SIGILL\n");
            break;
        default:
            perror("signal_handler");
            break;
    }
}

int main(void) {
    signal(SIGHUP, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGILL, signal_handler);
    while (1)
        ;
    return 0;
}
