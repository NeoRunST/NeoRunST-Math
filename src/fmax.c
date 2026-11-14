double fmax(double x, double y) {
    if (__builtin_isnan(x)) return y;
    if (__builtin_isnan(y)) return x;
    return x > y ? x : y;
}
