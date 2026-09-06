---
title: xvm x86 node 性能对比实验
author: deepseek
date: 2026-09-07
---

本次实验基于 commit `2f3b51a9b`（gc 移到内存分配点之后、任何后续优化之前）。
测试例子为 `meta-lisp.meta` 的 `check`（自举编译器检查自身源码，
用自身 `bin/meta-lisp.meta` 跑 = xvm 后端，用 `bin/meta-lisp.js` 跑 = node 后端）。
对比仓库为 `/home/xyh/backup/x-lisp`（同一 commit）。

# 实验一：opcode 计数插桩

对 xvm 的 threaded handler 临时插桩，逐 opcode 统计执行次数：

- 总指令 **356,401,619**（约 3.56 亿条），单指令成本约 27ns。
- `load-result`（0x09）**105,947,543** 条，占 29.7% —— 全部来自非 tail 的
  `call`/`call-prim`/`apply`（每个调用后一条 `load-result`，与调用数 1:1）。
- prim 调用合计约 9,900 万次（占指令 28%）；`branch` 约 4,000 万次；
  `gc` 指令执行 469 万次，但**真正触发的收集只有 39 次**。
- 分配的 GC 对象合计约 1,030 万个（回收 950 万 + 存活 84.5 万）。

# 实验二：load-result 优化（call-prim 带 dest）—— 被证伪

让 `call-prim` 指令带 dest 操作数、结果直写局部变量，消除其后的 `load-result`：

- 字节码指令 -20.4%（356.4M → 283.6M），load-result 降 68.7%（105.9M → 33.2M）；
- 但 AB 交替实测（backup vs 优化版）：时间 14.4s → 14.1s，**几乎不变**；
- perf 硬件计数：**CPU 原生指令仅 -1.3%**（39.75G → 39.23G）。

结论：被削掉的 load-result 在 C 层只对应约 10 条原生指令（读 result、写 locals、
跳转），被处理器流水线吸收为"泡沫"，准零成本。**指令数不是这台机器上 xvm
的瓶颈**；"时间 ∝ 指令数" 对该负载不成立。

# 实验三：gprof 时间采样

`-pg -fno-lto` 重编译整条依赖链，对 self-check 采样（backup 与 current 热点几乎一致）：

| 类别 | 占比 |
|---|---|
| malloc 族（`_int_malloc`+`malloc_consolidate`+`calloc`+`free`） | ~17% |
| 解释器 `xvm_execute`（self） | ~12% |
| tag 检查（`value_tag` 8.9 亿次 + `to_object` + `is_object`，未内联） | ~8.5% |
| hash/array（`hash_insert`/`array_get`/`array_length`/`array_push`/`value_hash_code`） | ~10.5% |
| GC（`gc_mark`+`gc_sweep`+`hash_free`） | ~8% |
| memcpy/拷贝 | ~5.4% |

# 实验四：perf 硬件计数（xvm vs node）

| 指标 | xvm | node |
|---|---|---|
| cycles | 26.4G | 20.4G |
| 原生指令 | 39.7G | 32.4G |
| IPC | 1.52 | 1.59 |
| branch-misses | 0.58% | 1.01% |
| cache-misses | **71.6%** | 42.2% |

**低 IPC（1.5 左右）是该负载的特征而非解释器缺陷**：同样的检查工作在 V8 JIT
上 IPC 也只有 1.59。负载本身 = 大量动态分配 + 散列 + 对象图遍历，内存延迟主导。

# 实验五（关键）：x86 后端（目前完全没有 GC）跑同一个 check

`x86.exe run build/main.x86.exe -- check`（x86 backend 编译产物）：

| 指标 | x86 | node（对照） |
|---|---|---|
| 时间（最优轮 / 中位） | 5.2-5.6s / 7.2s | 6.4s |
| IPC | **1.95** | 1.54 |
| cache-misses | **15.2%** | 42-49% |
| 峰值内存 | **3439 MB** | 323 MB |

- 最优轮（5.2-5.6s）**已经快于 node（6.37s）**，且 x86 的 cycles 比 node 少 23%：
  原生+紧凑代码的执行质量全面领先；
- 但无 GC 导致峰值内存 3.4GB（node 的 10 倍），页分配/内存带宽压力造成
  5.2-7.9s 的大幅波动——这把它拖到"中位落后 node"。

# 实验六：xvm 临时关闭 GC（th_gc 置空）

同一构建仅 `th_gc` 改为 no-op（不触发收集，gc 指令空转），对比：

| 指标 | xvm（gc on） | xvm（gc off） |
|---|---|---|
| 时间（交错中位） | 11.90s | 8.14s |
| IPC | 1.52 | **1.93** |
| cache-misses | 71.6% | **13.9%** |
| 峰值内存 | 556 MB | 3208 MB |

- **GC 净成本 +46%**（11.90 vs 8.14s）；
- 关掉 GC 后 xvm 的 IPC（1.93）与 cache-misses（13.9%）几乎与原生 x86 相同
  （1.95 / 15.2%）—— **71.6% 的 cache-miss 几乎全部由 GC 造成**（mark 的对象图
  遍历 + sweep 全表扫描/整表复制），解释器调度本身对该负载并不差；
- 顺带测出 node 类型检查成本：去掉 LocatePass/CheckPass 后约 7.66s → 6.37s。

# 综合结论

| case | 时间(中位) | IPC | cache-misses | 峰值内存 |
|---|---|---|---|---|
| xvm（gc on） | 11.90s | 1.52 | 71.6% | 556 MB |
| xvm（gc off） | 8.14s | 1.93 | 13.9% | 3208 MB |
| x86（no gc） | 7.25s | 1.95 | 15.2% | 3439 MB |
| node | 6.37s | 1.54 | 42-49% | 323 MB |

1. xvm 的 GC（mark/sweep 全表遍历）既是时间（+46%）又是 cache（71.6%）的最大
   负担，是解释器端最有价值的研究方向。
2. 指令级优化（load-result 带 dest 等）对时间无效，已全部退回。
3. x86 后端执行质量最优（IPC 1.95、cache 15%），瓶颈是"无 GC 的内存压力"；
   **配 GC 后能否反超 node 取决于 GC 的实现成本，需实测验证**；其最优轮
   （5.2-5.6s）已快于 node（6.37s）的客观事实记录在上文两节。