#include <pthread.h>  
#include <stdlib.h>  
#include <stdio.h>

pthread_key_t key;
pthread_key_t key1;
pthread_key_t key2;

void *tthread_fun(void* args){
	pthread_setspecific(key,args);
	int *tmp = (int*)pthread_getspecific(key);
	printf("thread %lu private address: %p\n",pthread_self(),tmp);
	*tmp+=1;
	return (void*)0;		
}
 
int main(){

        pthread_t pid[3];

	pthread_key_create(&key,NULL);
	pthread_key_create(&key1,NULL);
	pthread_key_create(&key2,NULL);
        printf("key=%d\n",key);
        printf("key1=%d\n",key1);
        printf("key2=%d\n",key2);

	int a[3]={100,200,300};
        printf("the address of array is: %p\n",&a);
	
	int i=0;
	for(i=0;i<3;i++){
		pthread_create(&pid[i],NULL,tthread_fun,&a[i]);
	}
	for(i=0;i<3;i++){
		pthread_join(pid[i],NULL);
 
	}
	printf("a[0]=%d\n",a[0]);
        printf("a[1]=%d\n",a[1]);
        printf("a[2]=%d\n",a[2]);
	return 0;
}
