#include "math.h"

float modff(float x, float* ip) {
    double di = 0.0;
    double df = modf((double)x, &di);
    *ip = (float)di;
    return (float)df;
}
