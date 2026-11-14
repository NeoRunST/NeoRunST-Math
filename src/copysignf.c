#include "math.h"

float copysignf(float x, float y) { return (float)copysign((double)x, (double)y); }
