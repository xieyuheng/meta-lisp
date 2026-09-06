---
title: array-push
---

# Type

```meta-lisp
(all (E) (-> E (array-t E) void-t))
```

# Description

Append an element at the end in-place.

# Examples

```meta-lisp
(let ((a (make-array)))
  (array-push 1 a)
  (array-push 2 a)
  a)
;; => (@array 1 2)
```
