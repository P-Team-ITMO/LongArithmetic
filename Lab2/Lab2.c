#include <stdio.h>

#define SIZE 32

struct uint1024_t {
    short data[SIZE];
};

struct uint1024_t from_uint(unsigned int x) {
    struct uint1024_t res;
    for (int i = 0; i < SIZE; i++)
        res.data[i] = 0;
    for (int i = 0; i < 4; i++) {
        res.data[i] = x % 256;
        x /= 256;
    }
    return res;
}
struct uint1024_t add_op(struct uint1024_t x, struct uint1024_t y) {
    struct uint1024_t res = from_uint(0);
    for (int i = 0; i < SIZE; i++) {
        short buffer = x.data[i] + y.data[i] + res.data[i];
        res.data[i] = buffer % 256;
        res.data[i] = buffer % 256;
        if (i + 1 < SIZE)
            res.data[i + 1] += buffer / 256;
    }
    return res;
}
struct uint1024_t negative(struct uint1024_t x) {
    for (int i = 0; i < SIZE; i++)
        x.data[i] ^= 255;
    return add_op(x, from_uint(1));
}

struct uint1024_t subtr_op(struct uint1024_t x, struct uint1024_t y) {
    return add_op(x, negative(y));
}
void printAll(struct uint1024_t x) {
    for (int i = 0; i < SIZE; i++)
        printf("%d ", x.data[i]);
    printf("\n");
}

int main() {
  
}
