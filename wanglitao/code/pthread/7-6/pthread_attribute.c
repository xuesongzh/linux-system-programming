#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sum = 0;

void *thread_start(void *arg) {
    int len = *(int *)arg;
    for (int i = 0; i < len; i++) {
        sum += i;
        printf("sub thead: sum = %d\n", sum);
    }
    printf("sub thread: exit\n");
    pthread_exit(NULL);
}

int main(void) {
    int status;
    pthread_t tid;
    int arg = 10;

    pthread_attr_t attr;
    status = pthread_attr_init(&attr);
    if (status != 0) {
        perror("pthread_attr_init");
        exit(EXIT_FAILURE);
    }

    // set/get thread stack size
    int stacksize = 0;
    pthread_attr_getstacksize(&attr, &stacksize);
    printf("stacksize = %d kb\n", stacksize / 1024);
    stacksize = 2 * 1024 * 1024;
    pthread_attr_setstacksize(&attr, stacksize);
    stacksize = 0;
    pthread_attr_getstacksize(&attr, &stacksize);
    printf("stacksize = %d kb\n", stacksize / 1024);

    // get/set thread detach state
    int detachstate;
    pthread_attr_getdetachstate(&attr, &detachstate);
    printf("thread detach state: %d\n", detachstate);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    // pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_getdetachstate(&attr, &detachstate);
    printf("thread detach state: %d\n", detachstate);

    pthread_create(&tid, &attr, thread_start, (void *)&arg);
    pthread_attr_destroy(&attr);

    // pthread_join (tid, NULL);
    printf("main thread: sum = %d\n", sum);
    printf("main thread: exit\n");
    pthread_exit(NULL);
    return 0;
}
