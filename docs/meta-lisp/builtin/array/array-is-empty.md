---
title: array-is-empty
---

# Type

```meta-lisp
(all (E) (-> (array-t E) bool-t))
```

# Description

Check if the array is empty.

# Examples

```meta-lisp
(array-is-empty (@array))      ;; => #t
(array-is-empty (@array 1))    ;; => #f
```
