#pragma once

// - The builtin symbol table maps names to addresses.
//   The loader resolves `extern` fixups by looking up this table.
// - The address is either a function code address (for primitives)
//   or a value cell address (for variables like true/false/void/types).
// - The table is hand-written static data, kept in sync with the
//   declarations in meta-builtin.meta (they are the source of truth).

typedef struct {
  const char *name;
  void *address;
} builtin_symbol_t;

extern const builtin_symbol_t builtin_symbols_en[];
extern const size_t builtin_symbols_en_count;

extern const builtin_symbol_t builtin_symbols_zh[];
extern const size_t builtin_symbols_zh_count;

void builtin_init(void);
const void *builtin_lookup(const char *name);