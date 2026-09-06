---
title: array-pop
---

# Type

```meta-lisp
(all (E) (-> (array-t E) E))
```

# Description

Pop an element from the end, returning it.

# Examples

```meta-lisp
(let ((a (@array 1 2 3)))
  (array-pop a))  ;; => 3
```
