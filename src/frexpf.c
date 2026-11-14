#include "math.h"

float frexpf(float x, int* e) {
    double d = frexp((double)x, e);
    return (float)d;
}
