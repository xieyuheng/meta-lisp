---
title: array-to-list
---

# Type

```meta-lisp
(all (E) (-> (array-t E) (list-t E)))
```

# Description

Convert the array to an immutable list.

# Examples

```meta-lisp
(array-to-list (@array 1 2 3))  ;; => (@list 1 2 3)
```
