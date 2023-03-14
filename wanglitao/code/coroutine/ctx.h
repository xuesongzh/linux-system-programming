#ifndef __CTX_H__
#define __CTX_H__


int coroutine_create (void (*fn)(void *), void *args, unsigned int size); 
int coroutine_yield (void);
int coroutine_resume (int co_id);
    

#endif
