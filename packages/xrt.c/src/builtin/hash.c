#include "index.h"

value_t x_make_hash(void) {
  return x_object(make_xhash());
}

value_t x_is_any_hash(value_t value) {
  return x_bool(is_xhash(value));
}

value_t x_hash_copy(value_t hash) {
  return x_object(xhash_copy(to_xhash(hash)));
}

value_t x_hash_length(value_t hash) {
  return x_int(xhash_length(to_xhash(hash)));
}

value_t x_hash_is_empty(value_t hash) {
  return x_bool(xhash_is_empty(to_xhash(hash)));
}

value_t x_hash_get(value_t key, value_t hash) {
  return xhash_get(to_xhash(hash), key);
}

value_t x_hash_has(value_t key, value_t hash) {
  return x_bool(xhash_has(to_xhash(hash), key));
}

value_t x_hash_put_mut(value_t key, value_t value, value_t hash) {
  xhash_put(to_xhash(hash), key, value);
  return x_void;
}

value_t x_hash_put(value_t key, value_t value, value_t hash) {
  value_t copy = x_hash_copy(hash);
  xhash_put(to_xhash(copy), key, value);
  return copy;
}

value_t x_hash_delete_mut(value_t key, value_t hash) {
  xhash_delete(to_xhash(hash), key);
  return x_void;
}

value_t x_hash_delete(value_t key, value_t hash) {
  value_t copy = x_hash_copy(hash);
  xhash_delete(to_xhash(copy), key);
  return copy;
}

value_t x_hash_keys(value_t hash) {
  value_t keys = x_make_array();

  hash_iter_t iter;
  hash_iter_init(&iter, to_xhash(hash)->hash);
  const hash_entry_t *entry = hash_iter_next_entry(&iter);
  while (entry) {
    x_array_push_mut((value_t) entry->key, keys);
    entry = hash_iter_next_entry(&iter);
  }

  return x_array_to_list(keys);
}

value_t x_hash_values(value_t hash) {
  value_t values = x_make_array();

  hash_iter_t iter;
  hash_iter_init(&iter, to_xhash(hash)->hash);
  const hash_entry_t *entry = hash_iter_next_entry(&iter);
  while (entry) {
    x_array_push_mut((value_t) entry->value, values);
    entry = hash_iter_next_entry(&iter);
  }

  return x_array_to_list(values);
}

value_t x_hash_entries(value_t hash) {
  value_t entries = x_make_array();

  hash_iter_t iter;
  hash_iter_init(&iter, to_xhash(hash)->hash);
  const hash_entry_t *entry = hash_iter_next_entry(&iter);
  while (entry) {
    value_t key = (value_t) entry->key;
    value_t value = (value_t) entry->value;
    x_array_push_mut(x_make_pair(key, value), entries);
    entry = hash_iter_next_entry(&iter);
  }

  return x_array_to_list(entries);
}
