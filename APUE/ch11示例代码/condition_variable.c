#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock_s;
pthread_cond_t cond_sum_ready;

int sum;

void* Thread1(void* argv)
{
  while(1)
  {
     pthread_mutex_lock(&lock_s);
     sum++;
     pthread_mutex_unlock(&lock_s);

     if(sum>=100){
       printf("thread1 notify thread2\n");
       pthread_cond_signal(&cond_sum_ready);/* notification */
       pthread_exit(NULL);
     }
  }
}

void* Thread2(void* argv)
{
  pthread_mutex_lock(&lock_s);

  /* 1.pthread_cond_wait()需要传入一个已经加锁的互斥锁，该函数把调用线程加入等待条件的调用列表中，然后释放互斥锁，
   *   在条件满足从而离开pthread_cond_wait()时，mutex将被重新加锁 */
  /* 2.线程被唤醒后，它将重新检查判断条件是否满足，如果还不满足，一般说来线程应该仍阻塞在这里，被等待被下一次唤醒。这个过程一般用 while语句实现*/
  while(sum<100)
    pthread_cond_wait(&cond_sum_ready, &lock_s);/* waiting */

  printf("thread2: now sum is over 100!\n");
  sum=0;
  pthread_mutex_unlock(&lock_s);
  pthread_exit(NULL);
} 

int main()
{
   pthread_t tida, tidb;
   pthread_mutex_init(&lock_s, NULL);
   pthread_cond_init(&cond_sum_ready, NULL);

   pthread_create(&tida, NULL, Thread1, NULL);
   pthread_create(&tidb, NULL, Thread2, NULL);

   pthread_join(tida, NULL);
   pthread_join(tidb, NULL);

   pthread_mutex_destroy(&lock_s);
   pthread_cond_destroy(&cond_sum_ready);
   return 0;
}
