---
title: is-array
---

# Type

```meta-lisp
(all (A) (-> A bool-t))
```

# Description

Check if a value is an array.

# Examples

```meta-lisp
(is-array (make-array))         ;; => #t
(is-array (@array 1 2 3))       ;; => #t
(is-array (@list 1 2 3))        ;; => #f
```
