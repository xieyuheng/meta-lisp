---
title: array-length
---

# Type

```meta-lisp
(all (E) (-> (array-t E) int-t))
```

# Description

Array length.

# Examples

```meta-lisp
(array-length (@array))        ;; => 0
(array-length (@array 1 2 3))  ;; => 3
```
