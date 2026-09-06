---
title: array-each
---

# Type

```meta-lisp
(all (A Any) (-> (-> A Any) (array-t A) void-t))
```

# Description

Iterate over the elements with side effects.

# Examples

```meta-lisp
(array-each print (@array 1 2 3))
```
