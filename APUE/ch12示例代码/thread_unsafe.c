#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>
#include <string.h>
#include <libgen.h>
 
void* basename_test(void *arg) {
   pthread_t self = pthread_self();
   char *base = basename((char*)arg);
   printf("TI-%u: base: %s\n", self, base);
}
 
int main(int argc, char *argv) {
 
   int i = 0;
   pthread_t tids[2];
   char msg[1024];
   strcpy(msg, "/tmp/test");
 
   pthread_create(&tids[0], NULL, basename_test, msg);
   msg[7] -= 32;
   pthread_create(&tids[1], NULL, basename_test, msg);
 
   pthread_join(tids[0], NULL);
   pthread_join(tids[1], NULL);
   return 0;
}
