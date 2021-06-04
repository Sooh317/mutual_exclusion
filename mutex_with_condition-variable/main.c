#ifndef _REENTRANT
#define _REENTRANT
#endif
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include "bb.h"
#define MAX 10000
#define THREAD_SIZE 5

BB bb;
pthread_t threads[THREAD_SIZE];

void* thread_func1(){
    int i, j;
    int cnt_in = 0, cnt_out = 0;
    for(i = 0; i < MAX / (BUF_SIZE - 1); i++){
        for(j = 0; j < BUF_SIZE - 1; j++) bb_put(&bb, cnt_in++);
        for(j = 0; j < BUF_SIZE - 1; j++) assert(bb_get(&bb) == cnt_out++);
    }
    pthread_exit(NULL);
}

void* thread_func2(){
    int i, cnt = 0;
    for(i = 0; i < MAX / THREAD_SIZE; i++){
        bb_put(&bb, cnt++);
        printf("%d\n", bb_get(&bb));
    }
    pthread_exit(NULL);
}

void test1(){
    int i = 0;
    bb_init(&bb);
    if(pthread_create(&threads[i], NULL, thread_func1, &i) != 0){
        perror("pthread create failed\n");
        exit(1);
    };
    if(pthread_join(threads[i], NULL) != 0){
        perror("pthread join failed\n");
        exit(1);
    };
    return;
}

void test2(){
    int i;
    bb_init(&bb);
    for(i = 0; i < THREAD_SIZE; i++){
        if(pthread_create(&threads[i], NULL, thread_func2, &i) != 0){
            perror("pthread create failed\n");
            exit(1);
        };
    }
    for(i = 0; i < THREAD_SIZE; i++){
        if(pthread_join(threads[i], NULL) != 0){
            perror("pthread join failed\n");
            exit(1);
        };
    }
}

int main(){
    test1();
    test2();
    return 0;
}
