#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

int gCount = 0;

/* case1: normal situation */
void *thread_count(void* arg)
{
  int i = 0;
  while(i < 5000)
  {
       gCount++;
       i++;
  }
}

/* case2: 为了模拟这种数据不一致的问题,我们加大线程间切换*/
/* 加入局部变量tmp,使其代替gCount进行++操作,将数据++的过程分成两部分,
 * 并且插入一个printf调用,它会执行write系统调用进内核,为内核调度别的线程执行提供了一个时机*/
void *thread_count2(void* arg)
{
  int i = 0;
  int tmp = 0;
  while(i < 5000)
  {
       pthread_mutex_lock(&mutex);
       tmp = gCount;
       i++;
       printf("thread id: %u, count: %d\n",pthread_self(),gCount);
       gCount = tmp + 1;
       pthread_mutex_unlock(&mutex);
  }
}

int main()
{
   pthread_t tid1, tid2;

   pthread_mutex_init(&mutex,NULL);

   pthread_create(&tid1, NULL, thread_count2, NULL);
   pthread_create(&tid2, NULL, thread_count2, NULL);

   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);

   pthread_mutex_destroy(&mutex);
   printf("result: %d\n",gCount);
}
