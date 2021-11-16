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
void printAll(struct uint1024_t x) {
    for (int i = 0; i < SIZE; i++)
        printf("%d ", x.data[i]);
    printf("\n");
}

int main() {
    struct uint1024_t a, b;
    scanf_value(&a);
    scanf_value(&b);
    struct uint1024_t c = div_op(a, b);
    printf_value(c);
}
