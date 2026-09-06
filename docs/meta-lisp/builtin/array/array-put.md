---
title: array-put
---

# Type

```meta-lisp
(all (E) (-> int-t E (array-t E) void-t))
```

# Description

Replace the element at index in-place.

# Examples

```meta-lisp
(let ((a (@array 1 2 3)))
  (array-put 0 9 a)
  a)
;; => (@array 9 2 3)
```
