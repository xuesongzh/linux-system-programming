#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;

long int sum = 0;

void *pth_wr(void *arg)
{
    int i = (int)arg;

    pthread_rwlock_wrlock(&rwlock);//请求写锁
    printf("write================全局变量sum = %ld, 我是%d号线程。\n", sum += 40, i + 1);
    pthread_rwlock_unlock(&rwlock);//解锁
    sleep(1);
    pthread_exit(0);
} 

void *pth_rd(void *arg)
{
    int i = (int)arg;

    pthread_rwlock_rdlock(&rwlock);//请求读锁
    printf("read===================全局变量sum = %ld, 我是%d号线程。\n", sum, i + 1);
    pthread_rwlock_unlock(&rwlock);//解锁
    sleep(1);
    pthread_exit(0);
}

int main(void)
{

    pthread_t pth[10];

    int i, j;

    pthread_rwlock_init(&rwlock, NULL);

    for (i = 0; i != 3; i++)//写
    {
        pthread_create(&pth[i], NULL, pth_wr, (void *)i);
    }

    for (i = 0; i != 7; i++)//读
    {
        pthread_create(&pth[3 + i], NULL, pth_rd, (void *)(3+i));
    }

    sleep(5);

    for (j = 0; j != 10; j++)
    {
        pthread_detach(pth[j]);//回收线程
    }
    pthread_rwlock_destroy(&rwlock);
    return 0;
} 
