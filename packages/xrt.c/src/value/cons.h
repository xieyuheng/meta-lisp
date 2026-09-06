#pragma once

extern const object_class_t cons_class;

struct cons_t {
  struct object_header_t header;
  value_t car;
  value_t cdr;
};

typedef struct list_builder_t {
  value_t head;
  value_t tail;
} list_builder_t;

cons_t *make_cons(value_t car, value_t cdr);
void cons_free(cons_t *self);

list_builder_t list_builder_empty(void);
void list_builder_append(list_builder_t *self, value_t value);
value_t list_builder_result(const list_builder_t *self);

bool is_cons(value_t value);
cons_t *to_cons(value_t value);

bool cons_equal(const cons_t *lhs, const cons_t *rhs);
void write_cons(buffer_t *buffer, object_circle_ctx_t *ctx, const cons_t *self);
hash_code_t cons_hash_code(const cons_t *self);
ordering_t cons_compare(const cons_t *lhs, const cons_t *rhs);

cons_child_iter_t *make_cons_child_iter(const cons_t *cons);
void cons_child_iter_free(cons_child_iter_t *self);
object_t *cons_child_iter_next(cons_child_iter_t *iter);