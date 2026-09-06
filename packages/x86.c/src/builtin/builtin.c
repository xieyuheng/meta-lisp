#include "index.h"

void builtin_init(void) {
  builtin_init_en();
  builtin_init_zh();
}

static const void *lookup_in(const builtin_symbol_t *symbols, size_t count, const char *name) {
  for (size_t i = 0; i < count; i++) {
    if (string_equal(symbols[i].name, name)) {
      return symbols[i].address;
    }
  }
  return NULL;
}

const void *builtin_lookup(const char *name) {
  const void *address = lookup_in(builtin_symbols_en, builtin_symbols_en_count, name);
  if (address != NULL) return address;
  return lookup_in(builtin_symbols_zh, builtin_symbols_zh_count, name);
}