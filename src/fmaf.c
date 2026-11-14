#include "math.h"

float fmaf(float x, float y, float z) {
    return (float)((double)x * (double)y + (double)z);
}
