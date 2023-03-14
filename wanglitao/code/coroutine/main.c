#include <stdio.h>
#include "ctx.h"

#define MY_SIZE (1024 * 32)

void coroutine_read (void *args)
{
    puts ("coroutine_read start");
    coroutine_yield ();
    int data = *(char *) args;
    printf ("read coroutine read data: %d\n", data);
    puts ("coroutine_read exit");
}

void coroutine_write (void *args)
{
    puts ("coroutine_write start");
    *(char *)args = 100;
    puts (" write coroutine write data success");
    coroutine_yield ();
    puts ("coroutine_write exit");
}

int main (void)
{
    int rd_id;
    int wr_id;
    char buf[512];
    rd_id = coroutine_create (coroutine_read, buf, 0);
    wr_id = coroutine_create (coroutine_write, buf, 0);
    coroutine_resume (rd_id);
    coroutine_resume (wr_id);
    puts ("main exit");
    return 0;
}
