#ifndef BB_H
#define BB_H
#define BUF_SIZE 11

typedef struct BoundedBuffer{
    int bb_buf[BUF_SIZE];
    int in, out;
} BB;

int bb_get(BB* bb);
void bb_put(BB* bb, int x);
void bb_init(BB* bb);

#endif
