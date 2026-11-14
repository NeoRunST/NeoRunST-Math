#ifndef _NEP_MATH_H
#define _NEP_MATH_H
// ── NEP math.h — libm 用户接口 (musl 移植) ──
// 实现在 dev\tools\math\*.c, buildnep 编译时逐个加进命令行即可:
//   buildnep.exe main.c dev\tools\math\exp.c ... -o out.nep
// 算法来自 musl (MIT), sqrt 用 SSE2 sqrtsd 内联汇编。
// x86-64 SSE2: FLT_EVAL_METHOD = 0。

// ── 常量宏 ──
#define M_E        2.7182818284590452354    // e
#define M_LOG2E    1.4426950408889634074    // log2(e)
#define M_LOG10E   0.43429448190325182765   // log10(e)
#define M_LN2      0.69314718055994530942   // ln(2)
#define M_LN10     2.30258509299404568402   // ln(10)
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.78539816339744830962   // pi/4
#define M_1_PI     0.31830988618379067154   // 1/pi
#define M_2_PI     0.63661977236758134308   // 2/pi
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2  0.70710678118654752440   // 1/sqrt(2)

#define HUGE_VAL   (__builtin_huge_val())   // +inf
#define HUGE_VALF  (__builtin_huge_valf())
#define INFINITY   (__builtin_inff())
#define NAN        (__builtin_nanf(""))

#define isnan(x)    __builtin_isnan(x)
#define isinf(x)    __builtin_isinf(x)
#define isfinite(x) __builtin_isfinite(x)
#define signbit(x)  __builtin_signbit(x)

#define fpclassify(x) __builtin_fpclassify(0, 1, 2, 3, 4, (x))
#define isnormal(x)   (fpclassify(x) == 2)
#define isgreater(x, y)        __builtin_isgreater((x), (y))
#define isgreaterequal(x, y)   __builtin_isgreaterequal((x), (y))
#define isless(x, y)           __builtin_isless((x), (y))
#define islessequal(x, y)      __builtin_islessequal((x), (y))
#define islessgreater(x, y)    __builtin_islessgreater((x), (y))
#define isunordered(x, y)      __builtin_isunordered((x), (y))

// ── 函数声明 ──
double fabs(double x);
double ceil(double x);
double floor(double x);
double trunc(double x);
double round(double x);
double fmod(double x, double y);
double modf(double x, double *iptr);
double copysign(double x, double y);
double sqrt(double x);
double scalbn(double x, int n);

double exp(double x);
double expm1(double x);
double log(double x);
double log1p(double x);
double log10(double x);
double pow(double x, double y);

double sin(double x);
double cos(double x);
double tan(double x);
double asin(double x);
double acos(double x);
double atan(double x);
double atan2(double y, double x);

double sinh(double x);
double cosh(double x);
double tanh(double x);

#endif
