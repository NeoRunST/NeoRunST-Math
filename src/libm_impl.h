#ifndef _LIBM_IMPL_H
#define _LIBM_IMPL_H
// ── libm_impl.h — NEP freestanding libm 内部支撑头 ──
// 移植自 musl (MIT) src/math + src/internal/libm.h:
//   1. 替代 musl 的 <stdint.h>/<features.h>/libm.h/exp_data.h/log_data.h/pow_data.h
//   2. 算法与常数保持 musl 原样 (正确性关键), 只改外围
//   3. x86-64 SSE2: FLT_EVAL_METHOD=0, double_t = double
//
// musl 库及本移植均采用 MIT 许可。

// ── 基础整型 (LP64: int=32bit, long long=64bit) ──
typedef int                 int32_t;
typedef unsigned int        uint32_t;
typedef long long           int64_t;
typedef unsigned long long  uint64_t;

// ── 浮点环境 ──
#define FLT_EVAL_METHOD 0
#define LDBL_MAX_EXP    1024    // 不用 long double: __rem_pio2_large 只需 66 项 2/pi 表
typedef double  double_t;
typedef float   float_t;

#define DBL_EPSILON  0x1p-52
#define LDBL_EPSILON 0x1p-63

// ── 特殊值与分类 (freestanding 下用 GCC 内建) ──
#define INFINITY (__builtin_inff())
#define NAN      (__builtin_nanf(""))
#define isnan(x)     __builtin_isnan(x)
#define isinf(x)     __builtin_isinf(x)
#define isfinite(x)  __builtin_isfinite(x)
#define signbit(x)   __builtin_signbit(x)

// ── musl 内部开关 ──
// 支持非就近舍入模式 / 支持 SNaN / 目标平台取整内建
#define WANT_ROUNDING 1
#define WANT_SNAN     0
#if WANT_SNAN
#error SNaN is unsupported
#else
#define issignalingf_inline(x) 0
#define issignaling_inline(x)  0
#endif

#ifndef TOINT_INTRINSICS
#define TOINT_INTRINSICS 0
#endif

// ── 分支预测提示 ──
#define predict_true(x)  __builtin_expect(!!(x), 1)
#define predict_false(x) __builtin_expect(x, 0)

// ── 求值屏障 (限制优化器对浮点表达式的变换; 同 musl libm.h) ──
static inline float eval_as_float(float x)
{
	float y = x;
	return y;
}

static inline double eval_as_double(double x)
{
	double y = x;
	return y;
}

static inline float fp_barrierf(float x)
{
	volatile float y = x;
	return y;
}

static inline double fp_barrier(double x)
{
	volatile double y = x;
	return y;
}

static inline void fp_force_evalf(float x)
{
	volatile float y;
	y = x;
	(void)y;
}

static inline void fp_force_eval(double x)
{
	volatile double y;
	y = x;
	(void)y;
}

// 确保表达式被求值 (只为 fenv 副作用, 结果丢弃)
#define FORCE_EVAL(x) do {                        \
	if (sizeof(x) == sizeof(float)) {         \
		fp_force_evalf(x);                \
	} else if (sizeof(x) == sizeof(double)) { \
		fp_force_eval(x);                 \
	} else {                                  \
		volatile long double __fe_y;      \
		__fe_y = (x);                     \
		(void)__fe_y;                     \
	}                                         \
} while(0)

// ── 位级 reinterpret (union 复合字面量, 同 musl libm.h) ──
#define asuint(f)   ((union{float _f; uint32_t _i;}){f})._i
#define asfloat(i)  ((union{uint32_t _i; float _f;}){i})._f
#define asuint64(f) ((union{double _f; uint64_t _i;}){f})._i
#define asdouble(i) ((union{uint64_t _i; double _f;}){i})._f

#define EXTRACT_WORDS(hi,lo,d)                 \
do {                                           \
  uint64_t __u = asuint64(d);                  \
  (hi) = __u >> 32;                            \
  (lo) = (uint32_t)__u;                        \
} while (0)

#define GET_HIGH_WORD(hi,d)                    \
do {                                           \
  (hi) = asuint64(d) >> 32;                    \
} while (0)

#define GET_LOW_WORD(lo,d)                     \
do {                                           \
  (lo) = (uint32_t)asuint64(d);                \
} while (0)

#define INSERT_WORDS(d,hi,lo)                  \
do {                                           \
  (d) = asdouble(((uint64_t)(hi)<<32) | (uint32_t)(lo)); \
} while (0)

#define SET_HIGH_WORD(d,hi)                    \
  INSERT_WORDS(d, hi, (uint32_t)asuint64(d))

#define SET_LOW_WORD(d,lo)                     \
  INSERT_WORDS(d, asuint64(d)>>32, lo)

#define GET_FLOAT_WORD(w,d)                    \
do {                                           \
  (w) = asuint(d);                             \
} while (0)

#define SET_FLOAT_WORD(d,w)                    \
do {                                           \
  (d) = asfloat(w);                            \
} while (0)

// ── 别名与可见性 ──
// musl 的 weak_alias 改成 GCC alias (别名目标必须在本编译单元内定义)
#define weak_alias(old, new) extern __typeof(old) new __attribute__((alias(#old)))
#define hidden               // 本镜像单文件链接, 可见性无意义

// ── 库内跨文件函数原型 (freestanding 无 math.h 可包含) ──
int    __rem_pio2_large(double*,double*,int,int,int);
int    __rem_pio2(double,double*);
double __sin(double,double,int);
double __cos(double,double);
double __tan(double,double,int);
double __expo2(double,double);

double __math_xflow(uint32_t, double);
double __math_uflow(uint32_t);
double __math_oflow(uint32_t);
double __math_divzero(uint32_t);
double __math_invalid(double);

// ── 公开函数原型 (库内互相调用: __expo2→exp, sinh/cosh/tanh→expm1,
//    asin/acos→sqrt, atan2→atan, __rem_pio2_large→floor/scalbn 等) ──
double fabs(double);
double ceil(double);
double floor(double);
double trunc(double);
double round(double);
double fmod(double, double);
double modf(double, double*);
double copysign(double, double);
double sqrt(double);
double scalbn(double, int);

double exp(double);
double expm1(double);
double log(double);
double log1p(double);
double log10(double);
double pow(double, double);

double sin(double);
double cos(double);
double tan(double);
double asin(double);
double acos(double);
double atan(double);
double atan2(double, double);

double sinh(double);
double cosh(double);
double tanh(double);

// ── exp_data.h (musl) ──
#define EXP_TABLE_BITS 7
#define EXP_POLY_ORDER 5
#define EXP_USE_TOINT_NARROW 0
#define EXP2_POLY_ORDER 5
extern const struct exp_data {
	double invln2N;
	double shift;
	double negln2hiN;
	double negln2loN;
	double poly[4]; /* Last four coefficients.  */
	double exp2_shift;
	double exp2_poly[EXP2_POLY_ORDER];
	uint64_t tab[2*(1 << EXP_TABLE_BITS)];
} __exp_data;

// ── log_data.h (musl) ──
#define LOG_TABLE_BITS 7
#define LOG_POLY_ORDER 6
#define LOG_POLY1_ORDER 12
extern const struct log_data {
	double ln2hi;
	double ln2lo;
	double poly[LOG_POLY_ORDER - 1]; /* First coefficient is 1.  */
	double poly1[LOG_POLY1_ORDER - 1];
	struct {
		double invc, logc;
	} tab[1 << LOG_TABLE_BITS];
#if !__FP_FAST_FMA
	struct {
		double chi, clo;
	} tab2[1 << LOG_TABLE_BITS];
#endif
} __log_data;

// ── pow_data.h (musl) ──
#define POW_LOG_TABLE_BITS 7
#define POW_LOG_POLY_ORDER 8
extern const struct pow_log_data {
	double ln2hi;
	double ln2lo;
	double poly[POW_LOG_POLY_ORDER - 1]; /* First coefficient is 1.  */
	/* Note: the pad field is unused, but allows slightly faster indexing.  */
	struct {
		double invc, pad, logc, logctail;
	} tab[1 << POW_LOG_TABLE_BITS];
} __pow_log_data;

#endif
