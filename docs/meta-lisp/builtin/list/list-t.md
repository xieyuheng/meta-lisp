---
title: list-t
---

# Type

```meta-lisp
type-t
```

# Description

List type constructor. `(list-t E)` represents an immutable list with element type `E`.

# Examples

```meta-lisp
(claim numbers (list-t int-t))
(claim names (list-t text-t))
```
