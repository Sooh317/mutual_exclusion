#ifndef BTREE_H
#define BTREE_H

typedef struct node{
    int val;
    int flag;
    struct node *left, *right, *parent;
}tnode;
tnode* btree_create(void);
void btree_insert(int v, tnode** t);
void btree_destroy(tnode** t);
void btree_dump(tnode* t);

#endif

