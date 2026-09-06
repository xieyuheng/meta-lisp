---
title: "@array"
---

# Description

Array literal. `(@array <exp> ...)` creates an array with the given elements, evaluating elements from left to right.

# Examples

```meta-lisp
(@array)          ;; => (@array)
(@array 1 2 3)    ;; => (@array 1 2 3)
(@array "a" "b")  ;; => (@array "a" "b")
```
