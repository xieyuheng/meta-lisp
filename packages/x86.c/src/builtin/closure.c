#include "index.h"

// - The x86 compiler translates lambda to: make-closure(fn, size) +
//   closure-put-arg(index, value, closure) ... and indirect calls via
//   closure-fn(closure) -> fn address. See [x86.c] closure object.
// - note: index / size arguments are tagged integers (like all primitives),
//   except fn which is the raw native code address (untagged).

value_t x86_make_closure(value_t fn_val, value_t size_val) {
  void *fn = (void *) fn_val;
  size_t size = (size_t) to_int64(size_val);
  x86_closure_t *closure = make_x86_closure(fn, size);
  return x_object(closure);
}

value_t x86_closure_put_arg_mut(value_t index_val, value_t value, value_t closure_val) {
  size_t index = (size_t) to_int64(index_val);
  x86_closure_t *closure = to_x86_closure(closure_val);
  closure->args[index] = value;
  return x_object(closure);
}

value_t x86_closure_arg(value_t index_val, value_t closure_val) {
  size_t index = (size_t) to_int64(index_val);
  x86_closure_t *closure = to_x86_closure(closure_val);
  return closure->args[index];
}

value_t x86_closure_fn(value_t closure_val) {
  x86_closure_t *closure = to_x86_closure(closure_val);
  // - note: the fn address is the raw native code address (untagged),
  //   the compiler calls it directly via `call [rax]`.
  return (value_t) closure->fn;
}