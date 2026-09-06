---
title: array-push-front
---

# Type

```meta-lisp
(all (E) (-> E (array-t E) void-t))
```

# Description

Prepend an element at the front in-place.

# Examples

```meta-lisp
(let ((a (@array 2 3)))
  (array-push-front 1 a)
  a)
;; => (@array 1 2 3)
```
