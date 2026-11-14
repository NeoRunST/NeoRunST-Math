#include "math.h"

float nextafterf(float x, float y) {
    if (isnan(x) || isnan(y)) return x + y;
    if (x == y) return y;
    unsigned int bits;
    __asm__ volatile("movd %1, %0" : "=r"(bits) : "x"(x));
    if (x == 0.0f) {
        bits = (y < 0.0f) ? 0x80000001u : 0x00000001u;
    } else if ((x > 0.0f) == (y > x)) {
        bits += 1;
    } else {
        bits -= 1;
    }
    float r;
    __asm__ volatile("movd %1, %0" : "=x"(r) : "r"(bits));
    return r;
}
