// ── mathtest.c — NEP libm (musl 移植) 数值验证 ──
// 控制台程序: 对每个函数验证已知值 (相对误差 1e-9 内; 取整/位操作类精确比较)。
// stdio.h 无 %f: double 打印用 ×1e9 转 %lld 的简易 dtoa。
#include "stdio.h"
#include "math.h"

static int npass = 0, nfail = 0;

// 简易 double 转串: 9 位小数, 整数/小数部分拆开走 %lld (stdio 无 %f)。
// 超大/超小值按量级缩放, 避免 ×1e9 溢出 long long。
static void pd(const char* tag, double v)
{
    double a = v < 0 ? -v : v;
    if (a >= 1e12) {                       // 整数近似
        printf("       %s %s%lld\n", tag, v < 0 ? "-" : "", (long long)v);
        return;
    }
    if (a > 0 && a < 1e-6) {               // 极小值: 以 e-18 表示
        long long m = (long long)(v * 1e18 + (v < 0 ? -0.5 : 0.5));
        printf("       %s %llde-18\n", tag, m < 0 ? -m : m);
        return;
    }
    long long s = (long long)(v * 1e9 + (v < 0 ? -0.5 : 0.5));
    long long ip = s / 1000000000;
    long long fp = s % 1000000000;
    if (fp < 0) fp = -fp;
    const char* sign = (v < 0 && ip == 0) ? "-" : "";
    printf("       %s %s%lld.%09lld\n", tag, sign, ip, fp);
}

// exact: 期望逐位相等 (取整/位操作函数); 否则相对误差 1e-9 (want 为 0 时按绝对误差 1e-9)
static void chk(const char* name, double got, double want, int exact)
{
    double err = got - want;
    if (err < 0) err = -err;
    double w = want < 0 ? -want : want;
    double tol = exact ? 0.0 : 1e-9 * (w > 1.0 ? w : 1.0);
    if (got == want || err <= tol) {
        npass++;
        printf("[PASS] %s\n", name);
    } else {
        nfail++;
        printf("[FAIL] %s\n", name);
        pd("got :", got);
        pd("want:", want);
    }
}

int nep_main(void)
{
    printf("=== NEP libm test (musl port) ===\n");

    // ── 位操作 / 取整类: 精确 ──
    chk("fabs(-3.5)",      fabs(-3.5),        3.5,                 1);
    chk("copysign(2.5,-1)", copysign(2.5, -1.0), -2.5,              1);
    chk("copysign(-2.5,3)", copysign(-2.5, 3.0), 2.5,               1);
    chk("ceil(-1.5)",      ceil(-1.5),        -1.0,                1);
    chk("ceil(2.1)",       ceil(2.1),         3.0,                 1);
    chk("floor(-1.5)",     floor(-1.5),       -2.0,                1);
    chk("floor(2.9)",      floor(2.9),        2.0,                 1);
    chk("trunc(-1.8)",     trunc(-1.8),       -1.0,                1);
    chk("trunc(1.8)",      trunc(1.8),        1.0,                 1);
    chk("round(2.5)",      round(2.5),        3.0,                 1);
    chk("round(-2.5)",     round(-2.5),       -3.0,                1);
    chk("round(2.4)",      round(2.4),        2.0,                 1);
    chk("fmod(5.5,2)",     fmod(5.5, 2.0),    1.5,                 1);
    chk("fmod(-5.5,2)",    fmod(-5.5, 2.0),   -1.5,                1);
    chk("scalbn(1.5,4)",   scalbn(1.5, 4),    24.0,                1);

    // modf: 整数部分 + 小数部分
    double ipart = 0.0;
    double fpart = modf(-1.5, &ipart);
    chk("modf(-1.5)->int", ipart,             -1.0,                1);
    chk("modf(-1.5)->frac", fpart,            -0.5,                1);

    // sqrt: 硬件 sqrtsd
    chk("sqrt(2)",         sqrt(2.0),         1.4142135623730951,  0);
    chk("sqrt(4)",         sqrt(4.0),         2.0,                 1);
    if (isnan(sqrt(-1.0)) && !isnan(sqrt(2.0))) {
        npass++;
        printf("[PASS] sqrt(-1)=NaN\n");
    } else {
        nfail++;
        printf("[FAIL] sqrt(-1)=NaN\n");
        pd("got :", sqrt(-1.0));
    }

    // ── 指数 / 对数 ──
    chk("exp(1)",          exp(1.0),          2.7182818284590452,  0);
    chk("exp(2)",          exp(2.0),          7.3890560989306502,  0);
    chk("exp(-1)",         exp(-1.0),         0.36787944117144233, 0);
    chk("expm1(1)",        expm1(1.0),        1.7182818284590452,  0);
    chk("expm1(1e-10)",    expm1(1e-10),      1.00000000005e-10,   0);
    chk("log(2)",          log(2.0),          0.69314718055994529, 0);
    chk("log(e)",          log(M_E),          1.0,                 0);
    chk("log(10)",         log(10.0),         2.3025850929940457,  0);
    chk("log1p(1)",        log1p(1.0),        0.69314718055994529, 0);
    chk("log1p(1e-10)",    log1p(1e-10),      0.99999999995e-10,   0);
    chk("log10(1000)",     log10(1000.0),     3.0,                 0);
    chk("log10(2)",        log10(2.0),        0.30102999566398120, 0);

    // ── 幂 ──
    chk("pow(2,10)",       pow(2.0, 10.0),    1024.0,              0);
    chk("pow(2,0.5)",      pow(2.0, 0.5),     1.4142135623730951,  0);
    chk("pow(-2,3)",       pow(-2.0, 3.0),    -8.0,                0);
    chk("pow(5,2)",        pow(5.0, 2.0),     25.0,                0);

    // ── 三角 ──
    chk("sin(1)",          sin(1.0),          0.84147098480789651, 0);
    chk("cos(1)",          cos(1.0),          0.54030230586813977, 0);
    chk("tan(1)",          tan(1.0),          1.5574077246549023,  0);
    chk("sin(pi)",         sin(M_PI),         0.0,                 0);
    chk("cos(pi)",         cos(M_PI),         -1.0,                0);
    chk("asin(0.5)",       asin(0.5),         0.52359877559829887, 0);
    chk("acos(0.5)",       acos(0.5),         1.0471975511965979,  0);
    chk("atan(1)",         atan(1.0),         0.78539816339744831, 0);
    chk("atan2(1,1)",      atan2(1.0, 1.0),   0.78539816339744831, 0);
    chk("atan2(-1,-1)",    atan2(-1.0, -1.0), -2.3561944901923448, 0);
    chk("atan2(1,-1)",     atan2(1.0, -1.0),  2.3561944901923448,  0);

    // ── 双曲 ──
    chk("sinh(1)",         sinh(1.0),         1.1752011936438014,  0);
    chk("cosh(1)",         cosh(1.0),         1.5430806348152437,  0);
    chk("tanh(1)",         tanh(1.0),         0.76159415595576485, 0);
    chk("sinh(-1)",        sinh(-1.0),        -1.1752011936438014, 0);

    // ── Lua 常用大参数路径 ──
    chk("sin(100)",        sin(100.0),        -0.50636564110975879, 0);
    chk("cos(1000)",       cos(1000.0),       0.56237907629070294, 0);
    chk("log(1e-300)",     log(1e-300),       -690.77552789821368, 0);
    chk("exp(700)",        exp(700.0),        1.0142320547350045e304, 0);

    printf("\n=== summary: %d passed, %d failed ===\n", npass, nfail);
    printf(nfail ? "RESULT: FAIL\n" : "RESULT: ALL PASS\n");
    return nfail != 0;
}
