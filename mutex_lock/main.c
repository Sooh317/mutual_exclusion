#ifndef _REENTRANT
#define _REENTRANT
#endif
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "btree.h"
#define SIZE 10

tnode *tree;
void* thread_func(void* arg);

int main(){
    pthread_t threads[SIZE];
    int i;
    tree = btree_create();

    for(i = 0; i < SIZE; i++){
        if(pthread_create(&threads[i], NULL, thread_func, &i) != 0){
            perror("pthread create failed\n");
            return 1;
        };
    }

    for(i = 0; i < SIZE; i++){
        if(pthread_join(threads[i], NULL) != 0){
            perror("pthread join failed\n");
            return 1;
        };
    }

    btree_dump(tree);
    btree_destroy(&tree);
    return 0;
}

void* thread_func(void* arg){
    int i;
    for(i = 0; i < 10000/SIZE; i++) btree_insert(i, &tree);
    pthread_exit(NULL);
}
