#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

// setjmp&longjmp example
jmp_buf buf;

int *p = NULL;

void handler() {
    //调用longjmp，参数buf是由setjmp函数所保存的堆栈环境，并使setjmp的返回值为1
    longjmp(buf, 1);
    //以下代码不会执行
    printf("never reach here\n");
}

int main() {
    // setjmp函数用缓冲区envbuf保存系统堆栈的内容，以便后续的longjmp函数使用。setjmp函数初次启用时返回0值
    if (setjmp(buf)) {
        printf("back in main\n");
    } else {
        printf("first time through\n");
        handler();
    }
    // segment fault : 解引用一个空指针
    //*p = 30;

    char *mystr = "Hello"; /* 它指向的Hello是常字符串，不能修改(就是不能写操作)*/
    // mystr[0] = 'w';

    char mystr2[] = "World"; /* 字符串Hello不是常字符串，可以修改 */
    // mystr2[0] = 'h';
    return 0;
}
