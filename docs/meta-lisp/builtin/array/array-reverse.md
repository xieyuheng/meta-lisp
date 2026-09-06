---
title: array-reverse
---

# Type

```meta-lisp
(all (E) (-> (array-t E) void-t))
```

# Description

Reverse the array in-place.

# Examples

```meta-lisp
(let ((a (@array 1 2 3)))
  (array-reverse a)
  a)
;; => (@array 3 2 1)
```
