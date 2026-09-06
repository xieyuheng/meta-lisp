---
title: array-t
---

# Type

```meta-lisp
type-t
```

# Description

Array type constructor. `(array-t E)` represents a mutable array with element type `E`.

# Examples

```meta-lisp
(claim numbers (array-t int-t))
(claim names (array-t text-t))
```
