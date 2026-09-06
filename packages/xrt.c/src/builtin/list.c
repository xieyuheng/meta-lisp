#include "index.h"

static void list_error(const char *message) {
  who_printf("(list) %s\n", message);
  exit(1);
}

value_t x_is_any_list(value_t value) {
  return x_bool(is_cons(value) || is_null(value));
}

value_t x_list_length(value_t list) {
  size_t length = 0;
  while (is_cons(list)) {
    length++;
    list = to_cons(list)->cdr;
  }
  return x_int(length);
}

value_t x_list_is_empty(value_t list) {
  return x_bool(is_null(list));
}

value_t x_list_get(value_t index, value_t list) {
  size_t i = to_int64(index);
  while (true) {
    if (is_null(list)) {
      list_error("(list-get) index out of range");
    }
    if (i == 0) {
      return to_cons(list)->car;
    }
    i--;
    list = to_cons(list)->cdr;
  }
}

static value_t list_copy_put(size_t i, value_t value, value_t list) {
  if (is_null(list)) {
    list_error("(list-copy-put) index out of range");
  }
  if (i == 0) {
    return x_cons(value, to_cons(list)->cdr);
  }
  return x_cons(
    to_cons(list)->car,
    list_copy_put(i - 1, value, to_cons(list)->cdr));
}

value_t x_list_put(value_t index, value_t value, value_t list) {
  return list_copy_put(to_int64(index), value, list);
}

value_t x_car(value_t list) {
  return to_cons(list)->car;
}

value_t x_cdr(value_t list) {
  return to_cons(list)->cdr;
}

value_t x_cons(value_t head, value_t tail) {
  return x_object(make_cons(head, tail));
}

value_t x_list_head(value_t list) {
  return x_car(list);
}

value_t x_list_rest(value_t list) {
  return x_cdr(list);
}

value_t x_list_but_last(value_t list) {
  if (is_null(list)) {
    list_error("(list-but-last) empty list");
  }
  if (is_null(to_cons(list)->cdr)) {
    return x_null;
  }
  return x_cons(to_cons(list)->car, x_list_but_last(to_cons(list)->cdr));
}

value_t x_list_last(value_t list) {
  while (is_cons(to_cons(list)->cdr)) {
    list = to_cons(list)->cdr;
  }
  return to_cons(list)->car;
}

value_t x_list_reverse(value_t list) {
  value_t result = x_null;
  while (is_cons(list)) {
    result = x_cons(to_cons(list)->car, result);
    list = to_cons(list)->cdr;
  }
  return result;
}

value_t x_list_to_set(value_t list) {
  xset_t *set = make_xset();
  while (is_cons(list)) {
    xset_add(set, to_cons(list)->car);
    list = to_cons(list)->cdr;
  }
  return x_object(set);
}