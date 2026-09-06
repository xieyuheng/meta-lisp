---
title: array-copy
---

# Type

```meta-lisp
(all (E) (-> (array-t E) (array-t E)))
```

# Description

Copy an array. The copy is not shared with the original.

# Examples

```meta-lisp
(let ((a (@array 1 2 3)))
  (array-copy a))  ;; => (@array 1 2 3)
```
