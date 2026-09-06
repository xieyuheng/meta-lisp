#include "../index.h"

// - smoke test of the x86_exe loader:
//   build a minimal exe in memory (mov rax, 42; ret), load it,
//   run the entry and check the return value.

static void put_u64(uint8_t *p, uint64_t v) {
  for (size_t i = 0; i < 8; i++) {
    p[i] = (uint8_t)(v >> (i * 8));
  }
}

static void put_u64_bytes(buffer_t *buffer, uint64_t v) {
  uint8_t bytes[8];
  put_u64(bytes, v);
  buffer_append_bytes(buffer, bytes, 8);
}

int main(void) {
  test_start();

  init_global_gc();
  builtin_init();

  // code: mov rax, 42 ; ret
  static const uint8_t code[] = {
    0x48, 0xc7, 0xc0, 0x2a, 0x00, 0x00, 0x00,   // mov rax, 42
    0xc3,                                       // ret
  };

  const size_t header_size = 14 * 8;
  const size_t code_file_offset = header_size;

  buffer_t *buffer = make_buffer();
  buffer_ensure_capacity(buffer, code_file_offset + sizeof(code));

  // header
  put_u64_bytes(buffer, 0x0000000000363878ull); // magic "x86\0\0\0\0"
  put_u64_bytes(buffer, 0);                     // version
  put_u64_bytes(buffer, code_file_offset);      // code_file_offset
  put_u64_bytes(buffer, sizeof(code));          // code_size
  put_u64_bytes(buffer, 0);                     // entry_code_segment_offset
  put_u64_bytes(buffer, 0);                     // data_file_offset
  put_u64_bytes(buffer, 0);                     // data_size
  put_u64_bytes(buffer, 0);                     // space_size
  put_u64_bytes(buffer, 0);                     // string_table_file_offset
  put_u64_bytes(buffer, 0);                     // string_table_size
  put_u64_bytes(buffer, 0);                     // label_table_file_offset
  put_u64_bytes(buffer, 0);                     // label_table_size
  put_u64_bytes(buffer, 0);                     // fixup_table_file_offset
  put_u64_bytes(buffer, 0);                     // fixup_table_size

  // code
  buffer_append_bytes(buffer, code, sizeof(code));

  x86_exe_t *exe = make_x86_exe(buffer);
  x86_exe_check(exe);
  x86_exe_load(exe);
  assert((int64_t) x86_exe_call_entry(exe) == 42);
  x86_exe_free(exe);

  test_end();
}