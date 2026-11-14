#include "math.h"

#define NR_ERF_EPS 1e-17
#define NR_ERF_MAXITER 200
#define NR_INV_SQRTPI 0.564189583547756286948

static double nr_erf_series(double x) {
    double x2 = x * x;
    double term = x;
    double sum = x;
    for (int n = 1; n < NR_ERF_MAXITER; n++) {
        term *= -x2 / (double)n;
        double add = term / (double)(2 * n + 1);
        sum += add;
        double aadd = add < 0 ? -add : add;
        if (aadd < NR_ERF_EPS) break;
    }
    return 2.0 * NR_INV_SQRTPI * sum;
}

static double nr_erfc_cf(double x) {
    double x2 = x * x;
    double tiny = 1e-300;
    double f = tiny;
    double c = f;
    double d = 0.0;
    for (int n = 1; n < NR_ERF_MAXITER; n++) {
        double a = (double)n / 2.0 / x2;
        d = 1.0 / (1.0 + a * d);
        if (d == 0.0) d = tiny;
        c = 1.0 + a / c;
        if (c == 0.0) c = tiny;
        double del = c * d;
        f *= del;
        double adel = del < 0 ? -del : del;
        if (adel < 1e-16) break;
    }
    return NR_INV_SQRTPI / x * f;
}

double erfc(double x) {
    if (isnan(x)) return x;
    if (x < 0.0) {
        if (x < -6.0) return 2.0;
        return 2.0 - nr_erf_series(-x);
    }
    if (x < 2.0) return 1.0 - nr_erf_series(x);
    if (x > 27.0) return 0.0;
    return exp(-x * x) * nr_erfc_cf(x);
}

double erf(double x) {
    if (isnan(x)) return x;
    double ax = x < 0 ? -x : x;
    if (ax > 27.0) return x < 0 ? -1.0 : 1.0;
    double v = ax < 3.0 ? nr_erf_series(ax) : 1.0 - exp(-ax * ax) * nr_erfc_cf(ax);
    return x < 0 ? -v : v;
}

float erfcf(float x) { return (float)erfc((double)x); }
float erff(float x) { return (float)erf((double)x); }
