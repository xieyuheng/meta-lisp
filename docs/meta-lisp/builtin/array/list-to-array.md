---
title: list-to-array
---

# Type

```meta-lisp
(all (E) (-> (list-t E) (array-t E)))
```

# Description

Convert an immutable list to an array.

# Examples

```meta-lisp
(list-to-array (@list 1 2 3))  ;; => (@array 1 2 3)
```
