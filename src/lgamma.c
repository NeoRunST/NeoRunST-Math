#include "math.h"

int signgam = 0;

static const double nr_lg_lanczos[9] = {
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

double lgamma(double z) {
    if (isnan(z)) return z;
    if (z == 0.0) return INFINITY;
    if (z < 0.5) {
        double s = sin(M_PI * z);
        signgam = s < 0 ? -1 : 1;
        double as = s < 0 ? -s : s;
        if (as == 0.0) return INFINITY;
        return log(M_PI / as) - lgamma(1.0 - z);
    }
    signgam = 1;
    z -= 1.0;
    double x = nr_lg_lanczos[0];
    for (int i = 1; i < 9; i++) x += nr_lg_lanczos[i] / (z + (double)i);
    double t = z + 7.5;
    return 0.5 * log(2.0 * M_PI) + (z + 0.5) * log(t) - t + log(x);
}

float lgammaf(float z) { return (float)lgamma((double)z); }
