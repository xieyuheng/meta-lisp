---
title: array-each-index
---

# Type

```meta-lisp
(all (A Any) (-> (-> int-t A Any) (array-t A) void-t))
```

# Description

Iterate over the elements with index.

# Examples

```meta-lisp
(array-each-index
  (lambda (i x) (println (make-pair i x)))
  (@array 'a 'b))
```
