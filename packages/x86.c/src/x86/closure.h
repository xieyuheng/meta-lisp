#pragma once

#include "deps.h"

// - The x86 closure is the runtime representation of a closure value.
//   Unlike xvm's closure (which holds a bytecode function_t*), the x86
//   closure holds the native code address of the function directly.

typedef struct x86_closure_child_iter_t x86_closure_child_iter_t;

extern const object_class_t x86_closure_class;

struct x86_closure_t {
  struct object_header_t header;
  void *fn;       // native code address
  size_t size;    // captured args count
  value_t *args;  // captured args
};

x86_closure_t *make_x86_closure(void *fn, size_t size);
void x86_closure_free(x86_closure_t *self);

bool is_x86_closure(value_t value);
x86_closure_t *to_x86_closure(value_t value);

bool x86_closure_equal(const x86_closure_t *lhs, const x86_closure_t *rhs);
void x86_closure_write(buffer_t *buffer, object_circle_ctx_t *ctx, const x86_closure_t *self);

x86_closure_child_iter_t *make_x86_closure_child_iter(const x86_closure_t *closure);
void x86_closure_child_iter_free(x86_closure_child_iter_t *self);
object_t *x86_closure_child_iter_next(x86_closure_child_iter_t *iter);