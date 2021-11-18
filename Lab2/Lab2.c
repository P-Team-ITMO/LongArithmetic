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
struct uint1024_t mult_simple(struct uint1024_t x, short y) {
    struct uint1024_t res = from_uint(0);
    for (int i = 0; i < SIZE; i++) {
        short buffer = res.data[i] + x.data[i] * y;
        res.data[i] = buffer % 256;
        if (i + 1 < SIZE)
            res.data[i + 1] = buffer / 256;
    }
    return res;
}

struct uint1024_t digit_shift(struct uint1024_t x, short y) {
    for (int i = SIZE - 1 - y; i >= 0; i--)
        x.data[i + y] = x.data[i];
    for (int i = 0; i < y; i++)
        x.data[i] = 0;
    return x;
}

struct uint1024_t digit_shift_s(struct uint1024_t x, short y) {
    for (int i = 0; i < SIZE - y; i++)
        x.data[i] = x.data[i + y];
    for (int i = SIZE - y; i < SIZE; i++)
        x.data[i] = 0;
    return x;
}

struct uint1024_t mult_op(struct uint1024_t x, struct uint1024_t y) {
    struct uint1024_t res = from_uint(0);
    for (int i = 0; i < SIZE; i++)
        res = add_op(res, digit_shift(mult_simple(x, y.data[i]), i));
    return res;
}
short isBigger(struct uint1024_t x, struct uint1024_t y) {
    for (int i = SIZE - 1; i >= 0; i--) {
        if (x.data[i] == y.data[i])
            continue;
        if (x.data[i] > y.data[i])
            return 1;
        return 0;
    }
    return 0;
}
short len(struct uint1024_t x) {
    for (int i = SIZE - 1; i >= 0; i--)
        if (x.data[i] > 0)
            return i + 1;
    return 0;
}
struct uint1024_t div_op(struct uint1024_t x, struct uint1024_t y) {
    struct uint1024_t res = from_uint(0);
    for (int i = 0; i < SIZE; i++) {
        short digits = i + 1;
        struct uint1024_t cutted = digit_shift_s(x, SIZE - digits);
        if (isBigger(y, cutted))
            continue;
        short digit = 0;
        while (!isBigger(mult_simple(y, digit), cutted))
            digit++;
        digit--;
        struct uint1024_t sub_res = digit_shift(mult_simple(y, digit), SIZE - 1 - i);
        x = subtr_op(x, sub_res);
        res.data[SIZE - 1 - i] = digit;
    }
    return res;
}
void printAll(struct uint1024_t x) {
    for (int i = 0; i < SIZE; i++)
        printf("%d ", x.data[i]);
    printf("\n");
}

int main() {
  
}
