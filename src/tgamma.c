#include "math.h"

static const double nr_lanczos[9] = {
    0.99999999999980993227684700473478,
    676.520368121885098567009190444019,
    -1259.13921672240287047156078755283,
    771.3234287776530788486528258894,
    -176.61502916214059906584551354,
    12.507343278686904814458936853,
    -0.13857109526572011689554707,
    9.984369578019570859563e-6,
    1.50563273514931155834e-7
};

static double nr_lanczos_sum(double z) {
    double x = nr_lanczos[0];
    for (int i = 1; i < 9; i++) x += nr_lanczos[i] / (z + (double)i);
    return x;
}

double tgamma(double z) {
    if (isnan(z)) return z;
    if (z == 0.0) return copysign(INFINITY, z);
    if (z < 0.5) {
        double s = sin(M_PI * z);
        if (s == 0.0) return NAN;
        return M_PI / (s * tgamma(1.0 - z));
    }
    z -= 1.0;
    double t = z + 7.5;
    double x = nr_lanczos_sum(z);
    return sqrt(2.0 * M_PI) * pow(t, z + 0.5) * exp(-t) * x;
}

float tgammaf(float z) { return (float)tgamma((double)z); }
