[xvm.c] gc

问题：

- 是否分配点只有可能是 prim？
- 可否统计哪些 prim 是有可能分配内存的，
  然后在编译时，给这些 prim 的调用前面，
  增加一个 gc 指令？

[x86.c] 给 x86 后端加 gc

# self-hosting

[meta-lisp.meta] [review] env.meta
[meta-lisp.meta] [review] apply.meta
[meta-lisp.meta] [review] evaluate.meta

[meta-lisp.meta] 110-locate-pass.meta
[meta-lisp.meta] 120-check-pass.meta
[meta-lisp.meta] 130-shrink-pass.meta
[meta-lisp.meta] 115-uniquify-pass.meta
[meta-lisp.meta] 150-lift-lambda-pass.meta
[meta-lisp.meta] 160-unnest-operand-pass.meta
[meta-lisp.meta] 170-explicate-control-pass.meta
[meta-lisp.meta] 180-codegen-pass.meta

# compile to native
# socket api and network programming
# http library
# write agent in meta-lisp
