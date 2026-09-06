#include "index.h"

// ---------------------------------------------------------------------------
// variable cells
// ---------------------------------------------------------------------------
// - true/false/void are compile-time constants, initialized directly.
// - type constants are produced by calling x_type_t() etc. at runtime
//   (they are lists), so they are initialized in builtin_init_en.

static value_t true_cell = x_true;
static value_t false_cell = x_false;
static value_t void_cell = x_void;
static value_t null_cell = x_null;

static value_t type_t_cell;
static value_t any_t_cell;
static value_t int_t_cell;
static value_t float_t_cell;
static value_t text_t_cell;
static value_t symbol_t_cell;
static value_t bool_t_cell;
static value_t void_t_cell;
static value_t file_t_cell;

void builtin_init_en(void) {
  type_t_cell = x_type_t();
  any_t_cell = x_any_t();
  int_t_cell = x_int_t();
  float_t_cell = x_float_t();
  text_t_cell = x_text_t();
  symbol_t_cell = x_symbol_t();
  bool_t_cell = x_bool_t();
  void_t_cell = x_void_t();
  file_t_cell = x_file_t();
}

// ---------------------------------------------------------------------------
// symbol table
// ---------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"

const builtin_symbol_t builtin_symbols_en[] = {
  // int

  { "meta-builtin/builtin/is-int", (void *) x_is_int },
  { "meta-builtin/builtin/ineg", (void *) x_ineg },
  { "meta-builtin/builtin/iadd", (void *) x_iadd },
  { "meta-builtin/builtin/isub", (void *) x_isub },
  { "meta-builtin/builtin/imul", (void *) x_imul },
  { "meta-builtin/builtin/idiv", (void *) x_idiv },
  { "meta-builtin/builtin/imod", (void *) x_imod },
  { "meta-builtin/builtin/int-max", (void *) x_int_max },
  { "meta-builtin/builtin/int-min", (void *) x_int_min },
  { "meta-builtin/builtin/int-greater", (void *) x_int_greater },
  { "meta-builtin/builtin/int-less", (void *) x_int_less },
  { "meta-builtin/builtin/int-greater-or-equal", (void *) x_int_greater_or_equal },
  { "meta-builtin/builtin/int-less-or-equal", (void *) x_int_less_or_equal },
  { "meta-builtin/builtin/int-is-positive", (void *) x_int_positive },
  { "meta-builtin/builtin/int-is-non-negative", (void *) x_int_non_negative },
  { "meta-builtin/builtin/int-is-non-zero", (void *) x_int_non_zero },
  { "meta-builtin/builtin/int-compare-ascending", (void *) x_int_compare_ascending },
  { "meta-builtin/builtin/int-compare-descending", (void *) x_int_compare_descending },
  { "meta-builtin/builtin/int-to-float", (void *) x_int_to_float },

  // float

  { "meta-builtin/builtin/is-float", (void *) x_is_float },
  { "meta-builtin/builtin/fneg", (void *) x_fneg },
  { "meta-builtin/builtin/fadd", (void *) x_fadd },
  { "meta-builtin/builtin/fsub", (void *) x_fsub },
  { "meta-builtin/builtin/fmul", (void *) x_fmul },
  { "meta-builtin/builtin/fdiv", (void *) x_fdiv },
  { "meta-builtin/builtin/fmod", (void *) x_fmod },
  { "meta-builtin/builtin/float-max", (void *) x_float_max },
  { "meta-builtin/builtin/float-min", (void *) x_float_min },
  { "meta-builtin/builtin/float-greater", (void *) x_float_greater },
  { "meta-builtin/builtin/float-less", (void *) x_float_less },
  { "meta-builtin/builtin/float-greater-or-equal", (void *) x_float_greater_or_equal },
  { "meta-builtin/builtin/float-less-or-equal", (void *) x_float_less_or_equal },
  { "meta-builtin/builtin/float-is-positive", (void *) x_float_positive },
  { "meta-builtin/builtin/float-is-non-negative", (void *) x_float_non_negative },
  { "meta-builtin/builtin/float-is-non-zero", (void *) x_float_non_zero },
  { "meta-builtin/builtin/float-compare-ascending", (void *) x_float_compare_ascending },
  { "meta-builtin/builtin/float-compare-descending", (void *) x_float_compare_descending },
  { "meta-builtin/builtin/float-to-int", (void *) x_float_to_int },

  // bool

  { "meta-builtin/builtin/true", &true_cell },
  { "meta-builtin/builtin/false", &false_cell },
  { "meta-builtin/builtin/is-bool", (void *) x_is_bool },
  { "meta-builtin/builtin/not", (void *) x_not },

  // void

  { "meta-builtin/builtin/void", &void_cell },
  { "meta-builtin/builtin/is-void", (void *) x_is_void },

  // type

  { "meta-builtin/builtin/type-t", &type_t_cell },
  { "meta-builtin/builtin/any-t", &any_t_cell },
  { "meta-builtin/builtin/int-t", &int_t_cell },
  { "meta-builtin/builtin/float-t", &float_t_cell },
  { "meta-builtin/builtin/text-t", &text_t_cell },
  { "meta-builtin/builtin/symbol-t", &symbol_t_cell },
  { "meta-builtin/builtin/bool-t", &bool_t_cell },
  { "meta-builtin/builtin/void-t", &void_t_cell },
  { "meta-builtin/builtin/file-t", &file_t_cell },
  { "meta-builtin/builtin/list-t", (void *) x_list_t },
  { "meta-builtin/builtin/array-t", (void *) x_array_t },
  { "meta-builtin/builtin/set-t", (void *) x_set_t },
  { "meta-builtin/builtin/hash-t", (void *) x_hash_t },
  { "meta-builtin/builtin/pair-t", (void *) x_pair_t },

  // value

  { "meta-builtin/builtin/is-atom", (void *) x_is_atom },
  { "meta-builtin/builtin/same", (void *) x_same },
  { "meta-builtin/builtin/equal", (void *) x_equal },
  { "meta-builtin/builtin/format", (void *) x_format },
  { "meta-builtin/builtin/hash-code", (void *) x_hash_code },
  { "meta-builtin/builtin/total-compare", (void *) x_total_compare },

  // file

  { "meta-builtin/builtin/open-input-file", (void *) x_open_input_file },
  { "meta-builtin/builtin/open-output-file", (void *) x_open_output_file },
  { "meta-builtin/builtin/file-close", (void *) x_file_close },
  { "meta-builtin/builtin/file-read", (void *) x_file_read },
  { "meta-builtin/builtin/file-write", (void *) x_file_write },
  { "meta-builtin/builtin/file-writeln", (void *) x_file_writeln },
  { "meta-builtin/builtin/print", (void *) x_print },
  { "meta-builtin/builtin/println", (void *) x_println },

  // path

  { "meta-builtin/builtin/path-file-name", (void *) x_path_file_name },
  { "meta-builtin/builtin/path-directory-name", (void *) x_path_directory_name },
  { "meta-builtin/builtin/path-extension", (void *) x_path_extension },
  { "meta-builtin/builtin/path-stem", (void *) x_path_stem },
  { "meta-builtin/builtin/path-is-absolute", (void *) x_path_is_absolute },
  { "meta-builtin/builtin/path-is-relative", (void *) x_path_is_relative },
  { "meta-builtin/builtin/path-join", (void *) x_path_join },
  { "meta-builtin/builtin/path-normalize", (void *) x_path_normalize },
  { "meta-builtin/builtin/path-relative", (void *) x_path_relative },
  { "meta-builtin/builtin/path-relative-to-cwd", (void *) x_path_relative_to_cwd },
  { "meta-builtin/builtin/path-resolve", (void *) x_path_resolve },

  // random

  { "meta-builtin/builtin/random-int", (void *) x_random_int },
  { "meta-builtin/builtin/random-float", (void *) x_random_float },

  // symbol

  { "meta-builtin/builtin/is-symbol", (void *) x_is_symbol },
  { "meta-builtin/builtin/symbol-length", (void *) x_symbol_length },
  { "meta-builtin/builtin/symbol-to-text", (void *) x_symbol_to_text },
  { "meta-builtin/builtin/symbol-append", (void *) x_symbol_append },
  { "meta-builtin/builtin/symbol-concat", (void *) x_symbol_concat },

  // string

  { "meta-builtin/builtin/is-text", (void *) x_is_text },
  { "meta-builtin/builtin/text-length", (void *) x_text_length },
  { "meta-builtin/builtin/text-is-empty", (void *) x_text_is_empty },
  { "meta-builtin/builtin/text-is-blank", (void *) x_text_is_blank },
  { "meta-builtin/builtin/text-slice", (void *) x_text_slice },
  { "meta-builtin/builtin/text-append", (void *) x_text_append },
  { "meta-builtin/builtin/text-concat", (void *) x_text_concat },
  { "meta-builtin/builtin/text-compare-lexical", (void *) x_text_compare_lexical },
  { "meta-builtin/builtin/text-to-symbol", (void *) x_text_to_symbol },
  { "meta-builtin/builtin/text-chars", (void *) x_text_chars },
  { "meta-builtin/builtin/text-lines", (void *) x_text_lines },
  { "meta-builtin/builtin/text-split", (void *) x_text_split },
  { "meta-builtin/builtin/text-join", (void *) x_text_join },
  { "meta-builtin/builtin/text-replace", (void *) x_text_replace },
  { "meta-builtin/builtin/text-is-prefix", (void *) x_text_is_prefix },
  { "meta-builtin/builtin/text-is-suffix", (void *) x_text_is_suffix },
  { "meta-builtin/builtin/text-to-upper-case", (void *) x_text_to_upper_case },
  { "meta-builtin/builtin/text-to-lower-case", (void *) x_text_to_lower_case },
  { "meta-builtin/builtin/text-get-code-point", (void *) x_text_get_code_point },
  { "meta-builtin/builtin/text-include", (void *) x_text_include },
  { "meta-builtin/builtin/text-find-index", (void *) x_text_find_index },
  { "meta-builtin/builtin/text-trim-left", (void *) x_text_trim_left },
  { "meta-builtin/builtin/text-trim-right", (void *) x_text_trim_right },
  { "meta-builtin/builtin/text-trim-start", (void *) x_text_trim_start },
  { "meta-builtin/builtin/text-trim-end", (void *) x_text_trim_end },
  { "meta-builtin/builtin/text-trim", (void *) x_text_trim },
  { "meta-builtin/builtin/text-is-int", (void *) x_text_is_int },
  { "meta-builtin/builtin/text-is-float", (void *) x_text_is_float },
  { "meta-builtin/builtin/text-to-int", (void *) x_text_to_int },
  { "meta-builtin/builtin/text-to-float", (void *) x_text_to_float },

  // list

  { "meta-builtin/builtin/null", &null_cell },
  { "meta-builtin/builtin/is-list", (void *) x_is_any_list },
  { "meta-builtin/builtin/car", (void *) x_car },
  { "meta-builtin/builtin/cdr", (void *) x_cdr },
  { "meta-builtin/builtin/cons", (void *) x_cons },

  // array

  { "meta-builtin/builtin/make-array", (void *) x_make_array },
  { "meta-builtin/builtin/is-array", (void *) x_is_any_array },
  { "meta-builtin/builtin/array-copy", (void *) x_array_copy },
  { "meta-builtin/builtin/array-length", (void *) x_array_length },
  { "meta-builtin/builtin/array-is-empty", (void *) x_array_is_empty },
  { "meta-builtin/builtin/array-pop", (void *) x_array_pop_mut },
  { "meta-builtin/builtin/array-push", (void *) x_array_push_mut },
  { "meta-builtin/builtin/array-pop-front", (void *) x_array_pop_front_mut },
  { "meta-builtin/builtin/array-push-front", (void *) x_array_push_front_mut },
  { "meta-builtin/builtin/array-get", (void *) x_array_get },
  { "meta-builtin/builtin/array-put", (void *) x_array_put_mut },
  { "meta-builtin/builtin/array-reverse", (void *) x_array_reverse_mut },
  { "meta-builtin/builtin/array-to-list", (void *) x_array_to_list },
  { "meta-builtin/builtin/list-to-array", (void *) x_list_to_array },

  // pair

  { "meta-builtin/builtin/make-pair", (void *) x_make_pair },
  { "meta-builtin/builtin/pair-first", (void *) x_pair_first },
  { "meta-builtin/builtin/pair-second", (void *) x_pair_second },
  { "meta-builtin/builtin/pair-put-first", (void *) x_pair_put_first },
  { "meta-builtin/builtin/pair-put-second", (void *) x_pair_put_second },

  // hash

  { "meta-builtin/builtin/make-hash", (void *) x_make_hash },
  { "meta-builtin/builtin/is-hash", (void *) x_is_any_hash },
  { "meta-builtin/builtin/hash-copy", (void *) x_hash_copy },
  { "meta-builtin/builtin/hash-length", (void *) x_hash_length },
  { "meta-builtin/builtin/hash-is-empty", (void *) x_hash_is_empty },
  { "meta-builtin/builtin/hash-get", (void *) x_hash_get },
  { "meta-builtin/builtin/hash-has", (void *) x_hash_has },
  { "meta-builtin/builtin/hash-put", (void *) x_hash_put_mut },
  { "meta-builtin/builtin/hash-copy-put", (void *) x_hash_put },
  { "meta-builtin/builtin/hash-delete", (void *) x_hash_delete_mut },
  { "meta-builtin/builtin/hash-keys", (void *) x_hash_keys },
  { "meta-builtin/builtin/hash-values", (void *) x_hash_values },
  { "meta-builtin/builtin/hash-entries", (void *) x_hash_entries },

  // set

  { "meta-builtin/builtin/make-set", (void *) x_make_set },
  { "meta-builtin/builtin/is-set", (void *) x_is_any_set },
  { "meta-builtin/builtin/set-copy", (void *) x_set_copy },
  { "meta-builtin/builtin/set-size", (void *) x_set_size },
  { "meta-builtin/builtin/set-is-empty", (void *) x_set_is_empty },
  { "meta-builtin/builtin/set-member", (void *) x_set_member },
  { "meta-builtin/builtin/set-add", (void *) x_set_add_mut },
  { "meta-builtin/builtin/set-copy-add", (void *) x_set_add },
  { "meta-builtin/builtin/set-delete", (void *) x_set_delete_mut },
  { "meta-builtin/builtin/set-copy-delete", (void *) x_set_delete },
  { "meta-builtin/builtin/set-clear", (void *) x_set_clear_mut },
  { "meta-builtin/builtin/set-union", (void *) x_set_union },
  { "meta-builtin/builtin/set-inter", (void *) x_set_inter },
  { "meta-builtin/builtin/set-difference", (void *) x_set_difference },
  { "meta-builtin/builtin/set-include", (void *) x_set_include },
  { "meta-builtin/builtin/set-disjoint", (void *) x_set_disjoint },
  { "meta-builtin/builtin/set-to-list", (void *) x_set_to_list },

  // assert

  { "meta-builtin/builtin/assert", (void *) x_assert },
  { "meta-builtin/builtin/assert-not", (void *) x_assert_not },
  { "meta-builtin/builtin/assert-equal", (void *) x_assert_equal },
  { "meta-builtin/builtin/assert-not-equal", (void *) x_assert_not_equal },
  { "meta-builtin/builtin/assert-with-location", (void *) x_assert_with_location },
  { "meta-builtin/builtin/assert-not-with-location", (void *) x_assert_not_with_location },
  { "meta-builtin/builtin/assert-equal-with-location", (void *) x_assert_equal_with_location },
  { "meta-builtin/builtin/assert-not-equal-with-location", (void *) x_assert_not_equal_with_location },

  // error

  { "meta-builtin/builtin/error", (void *) x_error },
  { "meta-builtin/builtin/error-with-location", (void *) x_error_with_location },

  // sexp

  { "meta-builtin/builtin/parse-sexps", (void *) x_parse_sexps },
  { "meta-builtin/builtin/format-as-sexp", (void *) x_format_as_sexp },
  { "meta-builtin/builtin/format-message-with-location", (void *) x_format_message_with_location },

  // json

  { "meta-builtin/builtin/parse-json", (void *) x_parse_json },
  { "meta-builtin/builtin/format-json", (void *) x_format_json },

  // fs

  { "meta-builtin/builtin/path-exists", (void *) x_path_exists },
  { "meta-builtin/builtin/path-is-file", (void *) x_path_is_file },
  { "meta-builtin/builtin/path-is-directory", (void *) x_path_is_directory },
  { "meta-builtin/builtin/path-read", (void *) x_path_read },
  { "meta-builtin/builtin/path-write", (void *) x_path_write },
  { "meta-builtin/builtin/path-list", (void *) x_path_list },
  { "meta-builtin/builtin/path-list-recursive", (void *) x_path_list_recursive },
  { "meta-builtin/builtin/path-ensure-file", (void *) x_path_ensure_file },
  { "meta-builtin/builtin/path-ensure-directory", (void *) x_path_ensure_directory },
  { "meta-builtin/builtin/path-delete-file", (void *) x_path_delete_file },
  { "meta-builtin/builtin/path-delete-directory", (void *) x_path_delete_directory },
  { "meta-builtin/builtin/path-delete", (void *) x_path_delete },
  { "meta-builtin/builtin/path-rename", (void *) x_path_rename },

  // closure
  // - note: the x86 compiler calls make-closure / closure-put-arg /
  //   closure-arg / closure-fn for lambda and indirect calls; they are
  //   implemented by x86 itself (see builtin/closure.c).

  { "meta-builtin/builtin/make-closure", (void *) x86_make_closure },
  { "meta-builtin/builtin/closure-put-arg", (void *) x86_closure_put_arg_mut },
  { "meta-builtin/builtin/closure-arg", (void *) x86_closure_arg },
  { "meta-builtin/builtin/closure-fn", (void *) x86_closure_fn },

  // process

  { "meta-builtin/builtin/exit", (void *) x_exit },
  { "meta-builtin/builtin/current-directory", (void *) x_current_directory },
  { "meta-builtin/builtin/current-command-line", (void *) x_current_command_line },
  { "meta-builtin/builtin/current-full-command-line", (void *) x_current_full_command_line },
  { "meta-builtin/builtin/current-stdout-file", (void *) x_current_stdout_file },
  { "meta-builtin/builtin/current-stderr-file", (void *) x_current_stderr_file },
};

#pragma GCC diagnostic pop

const size_t builtin_symbols_en_count =
  sizeof(builtin_symbols_en) / sizeof(builtin_symbols_en[0]);