#include "libm_impl.h"

double ldexp(double x, int n) {
    return scalbn(x, n);
}
