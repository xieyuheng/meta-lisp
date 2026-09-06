---
title: array-pop-front
---

# Type

```meta-lisp
(all (E) (-> (array-t E) E))
```

# Description

Pop an element from the front, returning it.

# Examples

```meta-lisp
(let ((a (@array 1 2 3)))
  (array-pop-front a))  ;; => 1
```
