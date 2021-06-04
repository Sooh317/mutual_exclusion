#ifndef _REENTRANT
#define _REENTRANT
#endif
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "btree.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

tnode* btree_create(){
    return NULL;
}

void btree_insert(int v, tnode **t){
    tnode *nw = (tnode*)malloc(sizeof(tnode));
    nw->val = v;
    nw->flag = 0;
    nw->left = NULL;
    nw->right = NULL;
    nw->parent = NULL;
    pthread_mutex_lock(&mutex);
    if(*t == NULL){
        *t = nw;
        pthread_mutex_unlock(&mutex);
        return;
    }
    tnode* cur = *t;
    while(1){
        if(v < cur->val){
            if(cur->left == NULL){
                nw->parent = cur;
                cur->left = nw;
                break;
            }
            cur = cur->left;
        }
        else{
            if(cur->right == NULL){
                nw->parent = cur;
                cur->right = nw;
                break;
            }
            cur = cur->right;
        }
    }
    pthread_mutex_unlock(&mutex);
}

void btree_destroy(tnode **t){
    if(t == NULL) return;
    tnode *cur = *t;
    while(1){
        if(cur->left == NULL){
            if(cur->right == NULL){
                if(cur->parent == NULL){
                    free(cur);
                    return;
                }
                tnode* p = cur->parent;
                int L = (p->left == cur) ? 0 : 1;
                if(L == 0) p->left = NULL;
                else p->right = NULL;
                free(cur);
                cur = p;
            }
            else cur = cur->right;
        }
        else cur = cur->left;
    }
}

void btree_dump(tnode *t){
    if(t == NULL) return;
    tnode *cur = t;
    while(1){
        if(cur->left == NULL){
            if(cur->flag == 0){
                printf("%d\n", cur->val);
                cur->flag = 1;
            }
            if(cur->right == NULL){
                if(cur->parent == NULL) return;
                tnode* p = cur->parent;
                int L = (p->left == cur) ? 0 : 1;
                if(L == 0) p->left = NULL;
                else p->right = NULL;
                cur = p;
            }
            else cur = cur->right;
        }
        else cur = cur->left;
    }
}
