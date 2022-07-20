#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

//复杂的声明
char* const* (*next)();

char s[] = "hello world\n";

char* const* example_fun() {
    return (char* const*)s;
}

/* 函数的返回值允许是一个函数指针 */
int fp() {
    return 1;
}

int (*fun())() {
    return fp;
}

/* 函数的返回值允许是一个指向数组的指针 */
int array[4] = {1, 2, 3, 4};

int (*fun1())[] {
    return array;
}
/* 数组里面允许有函数指针 */
int fa() {
}

int fb() {
}

/* signal函数使用举例 */
void signal_handler_fun(int signum) {
    printf("catch signal %d\n", signum);
}

int main() {
    // 复杂的声明
    next = example_fun;
    printf("%s", next());

    /* 函数的返回值允许是一个函数指针 */
    int (*fp)() = fun();
    printf("fp()=%d\n", fp());

    /* 函数的返回值允许是一个指向数组的指针 */
    int(*ap)[4] = fun1();
    printf("ap[3]=%d\n", (*ap)[3]);

    /* 数组里面允许有函数指针 */
    int (*fun2[])() = {fa, fb};

    /* 数组里面允许有其他数组 */
    int aa[2][2];

    /* signal函数使用举例 */
    signal(SIGINT, signal_handler_fun);
    while (1)
        ;

    return 0;
}
