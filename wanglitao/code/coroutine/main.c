#include <stdio.h>

#include "ctx.h"

#define MY_SIZE (1024 * 32)

void coroutine_read(void *args) {
    puts("coroutine_read start");
    coroutine_yield();
    int data = *(char *)args;
    printf("read coroutine read data: %d\n", data);
    puts("coroutine_read exit");
}

void coroutine_write(void *args) {
    puts("coroutine_write start");
    *(char *)args = 100;
    puts(" write coroutine write data success");
    coroutine_yield();
    puts("coroutine_write exit");
}

int main(void) {
    int rd_id;
    int wr_id;
    char buf[512];
    rd_id = coroutine_create(coroutine_read, buf, 0);
    wr_id = coroutine_create(coroutine_write, buf, 0);
    coroutine_resume(rd_id);
    coroutine_resume(wr_id);
    puts("main exit");
    return 0;
}

/*
线程开销：
    创建、销毁、上下文切换、同步
协程改进：
    调度开销小、不存在同步、死锁、资源竞争

实现协程的关键：
    上下文(寄存器、PC、堆栈)的维护

    ARM寄存器：R0-R15
    R0-R12 通用寄存器
    R13 堆栈指针sp
    R14 链接寄存器，使用BL跳转时，自动将下一条指令的地址保存到LR中
    R15 PC指针

    子程序通过寄存器R0-R3进行传参，多余的参数通过堆栈进行保存
    返回值：R0

*/
