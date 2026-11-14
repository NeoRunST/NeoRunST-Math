# neorunst-math

NeoRunST NEP SDK 的 freestanding 浮点数学库。

移植自 [musl libc](https://musl.libc.org/) 的 `src/math`（MIT 许可），
算法与常数保持 musl 原样，仅做了适配层改造以脱离 libc 依赖：

- `libm_impl.h`：内部支撑（typedef、`double_t`、`FORCE_EVAL`、
  `asuint64/asdouble`、`weak_alias` → GCC alias、`hidden` 置空）
- 删除全部 `#include <...>`，无 libc / libm / fenv 依赖
- `sqrt` 为内联汇编 `sqrtsd` 实现（musl 原实现依赖 fenv）

## 内容

- `math.h` — 用户接口头：函数声明 + `M_PI`/`M_E`/`HUGE_VAL`/`NAN` 等宏
- `src/` — 实现（每函数一个 .c，与 musl 文件一一对应）：
  exp/log/log10/expm1/log1p、sin/cos/tan（含大参数归约
  `__rem_pio2*`）、asin/acos/atan/atan2、sinh/cosh/tanh、
  floor/ceil/trunc/round/fabs/fmod/modf/copysign、scalbn、
  `__expo2`、`__math_*` 错误辅助、exp/log/pow 数据表
- `mathtest.c` — 测试程序（55 项断言，相对误差 1e-9）

## 构建（NeoRunST NEP SDK）

```sh
buildnep mathtest.c src/exp.c src/log.c ... -o mathtest.nep
```

## 许可

- 本库代码来自 musl libc，遵循 musl 的 MIT 许可，见 `LICENSE`。
- musl libc Copyright © 2005-2014 Rich Felker 等 musl 项目贡献者。
