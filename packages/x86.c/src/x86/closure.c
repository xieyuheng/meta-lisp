#include "index.h"

typedef struct x86_closure_child_iter_t {
  const x86_closure_t *closure;
  size_t index;
} x86_closure_child_iter_t;

const object_class_t x86_closure_class = {
  .name = "x86-closure",
  .equal_fn = (object_equal_fn_t *) x86_closure_equal,
  .write_fn = (object_write_fn_t *) x86_closure_write,
  .free_fn = (free_fn_t *) x86_closure_free,
  .make_child_iter_fn = (object_make_child_iter_fn_t *) make_x86_closure_child_iter,
  .child_iter_next_fn = (object_child_iter_next_fn_t *) x86_closure_child_iter_next,
  .child_iter_free_fn = (free_fn_t *) x86_closure_child_iter_free,
};

x86_closure_t *make_x86_closure(void *fn, size_t size) {
  x86_closure_t *self = new(x86_closure_t);
  self->header.class = &x86_closure_class;
  self->fn = fn;
  self->size = size;
  self->args = allocate_pointers(size);
  gc_add_object(global_gc, (object_t *) self);
  return self;
}

void x86_closure_free(x86_closure_t *self) {
  free(self->args);
  free(self);
}

bool is_x86_closure(value_t value) {
  return is_object(value) &&
    to_object(value)->header.class == &x86_closure_class;
}

x86_closure_t *to_x86_closure(value_t value) {
  if (!is_x86_closure(value)) {
    who_printf("expected x86 closure\n");
    exit(1);
  }
  return (x86_closure_t *) to_object(value);
}

bool x86_closure_equal(const x86_closure_t *lhs, const x86_closure_t *rhs) {
  if (lhs->fn != rhs->fn) return false;
  if (lhs->size != rhs->size) return false;
  if (lhs->args == rhs->args) return true;

  for (size_t i = 0; i < lhs->size; i++) {
    if (!equal(lhs->args[i], rhs->args[i])) return false;
  }

  return true;
}

void x86_closure_write(buffer_t *buffer, object_circle_ctx_t *ctx, const x86_closure_t *self) {
  write_template(buffer, "(@closure-fn %p [", self->fn);
  for (size_t i = 0; i < self->size; i++) {
    if (i > 0) write_template(buffer, " ");
    write_value_in_ctx(buffer, ctx, self->args[i]);
  }
  write_template(buffer, "])");
}

x86_closure_child_iter_t *make_x86_closure_child_iter(const x86_closure_t *closure) {
  x86_closure_child_iter_t *self = new(x86_closure_child_iter_t);
  self->closure = closure;
  self->index = 0;
  return self;
}

void x86_closure_child_iter_free(x86_closure_child_iter_t *self) {
  free(self);
}

object_t *x86_closure_child_iter_next(x86_closure_child_iter_t *iter) {
  while (iter->index < iter->closure->size) {
    value_t value = iter->closure->args[iter->index++];
    if (is_object(value)) {
      return to_object(value);
    }
  }
  return NULL;
}