#ifndef _REENTRANT
#define _REENTRANT
#endif
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "bb.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_not_full = PTHREAD_COND_INITIALIZER, c_not_empty = PTHREAD_COND_INITIALIZER;

void bb_init(BB* bb){
    bb->in = bb->out = 0;
    return;
}

void bb_put(BB* bb, int x){
    pthread_mutex_lock(&mutex);
    while((bb->in + 1) % BUF_SIZE == bb->out){ // queue is full 
        pthread_cond_wait(&c_not_full, &mutex);
    }
    int signal = (bb->in == bb->out ? 1 : 0);
    bb->bb_buf[bb->in++] = x;
    if(bb->in == BUF_SIZE) bb->in -= BUF_SIZE;
    if(signal) pthread_cond_signal(&c_not_empty);
    pthread_mutex_unlock(&mutex);
    return;
}

int bb_get(BB* bb){
    pthread_mutex_lock(&mutex);
    while(bb->in == bb->out){ // queue is empty
        pthread_cond_wait(&c_not_empty, &mutex);
    }
    int signal = ((bb->in + 1) % BUF_SIZE == bb->out ? 1 : 0);
    int ret = bb->bb_buf[bb->out++];
    if(bb->out == BUF_SIZE) bb->out -= BUF_SIZE;
    if(signal) pthread_cond_signal(&c_not_full);
    pthread_mutex_unlock(&mutex);
    return ret;
}
