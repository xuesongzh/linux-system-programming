#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
 * when a detached thread terminate,the resources of the thread wile be 
 * released automatically
 * but the resources of all threads are freed when the process terminates
 */

int sum = 0;

void * thread_start (void *arg)
{
    pthread_detach (pthread_self ());
    int len = *(int*)arg;
    for (int i = 0; i < len; i++)
    {
        sum += i;
        printf ("sub thread: sum = %d\n", sum);
        sleep (1);
    }
    printf ("sub thread: exit\n");
    pthread_exit (NULL);
}

int main (void)
{
    pthread_t tid;
    int arg = 10;
    pthread_create (&tid, NULL, thread_start, (void *) &arg);
    //pthread_detach (tid);
    printf ("sum = %d\n", sum);
    printf ("main thread: exit\n");
    pthread_exit (NULL);
    return 0;
}
