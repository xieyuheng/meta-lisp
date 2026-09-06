#include "index.h"

// ---------------------------------------------------------------------------
// variable cells
// ---------------------------------------------------------------------------
// - true/false/void are compile-time constants, initialized directly.
// - type constants are produced by calling x_type_t() etc. at runtime
//   (they are lists), so they are initialized in builtin_init_zh.

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

void builtin_init_zh(void) {
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

const builtin_symbol_t builtin_symbols_zh[] = {
  // int

  { "meta-builtin/内置/为整数", (void *) x_is_int },
  { "meta-builtin/内置/整数负", (void *) x_ineg },
  { "meta-builtin/内置/整数加", (void *) x_iadd },
  { "meta-builtin/内置/整数减", (void *) x_isub },
  { "meta-builtin/内置/整数乘", (void *) x_imul },
  { "meta-builtin/内置/整数除", (void *) x_idiv },
  { "meta-builtin/内置/整数模", (void *) x_imod },
  { "meta-builtin/内置/整数最大", (void *) x_int_max },
  { "meta-builtin/内置/整数最小", (void *) x_int_min },
  { "meta-builtin/内置/整数大于", (void *) x_int_greater },
  { "meta-builtin/内置/整数小于", (void *) x_int_less },
  { "meta-builtin/内置/整数大于等于", (void *) x_int_greater_or_equal },
  { "meta-builtin/内置/整数小于等于", (void *) x_int_less_or_equal },
  { "meta-builtin/内置/整数为正", (void *) x_int_positive },
  { "meta-builtin/内置/整数非负", (void *) x_int_non_negative },
  { "meta-builtin/内置/整数非零", (void *) x_int_non_zero },
  { "meta-builtin/内置/整数升序比较", (void *) x_int_compare_ascending },
  { "meta-builtin/内置/整数降序比较", (void *) x_int_compare_descending },
  { "meta-builtin/内置/整数转浮点", (void *) x_int_to_float },

  // float

  { "meta-builtin/内置/为浮点", (void *) x_is_float },
  { "meta-builtin/内置/浮点负", (void *) x_fneg },
  { "meta-builtin/内置/浮点加", (void *) x_fadd },
  { "meta-builtin/内置/浮点减", (void *) x_fsub },
  { "meta-builtin/内置/浮点乘", (void *) x_fmul },
  { "meta-builtin/内置/浮点除", (void *) x_fdiv },
  { "meta-builtin/内置/浮点模", (void *) x_fmod },
  { "meta-builtin/内置/浮点最大", (void *) x_float_max },
  { "meta-builtin/内置/浮点最小", (void *) x_float_min },
  { "meta-builtin/内置/浮点大于", (void *) x_float_greater },
  { "meta-builtin/内置/浮点小于", (void *) x_float_less },
  { "meta-builtin/内置/浮点大于等于", (void *) x_float_greater_or_equal },
  { "meta-builtin/内置/浮点小于等于", (void *) x_float_less_or_equal },
  { "meta-builtin/内置/浮点为正", (void *) x_float_positive },
  { "meta-builtin/内置/浮点非负", (void *) x_float_non_negative },
  { "meta-builtin/内置/浮点非零", (void *) x_float_non_zero },
  { "meta-builtin/内置/浮点升序比较", (void *) x_float_compare_ascending },
  { "meta-builtin/内置/浮点降序比较", (void *) x_float_compare_descending },
  { "meta-builtin/内置/浮点转整数", (void *) x_float_to_int },

  // bool

  { "meta-builtin/内置/真", &true_cell },
  { "meta-builtin/内置/假", &false_cell },
  { "meta-builtin/内置/为真假", (void *) x_is_bool },
  { "meta-builtin/内置/非", (void *) x_not },

  // void

  { "meta-builtin/内置/空值", &void_cell },
  { "meta-builtin/内置/为空值", (void *) x_is_void },

  // type

  { "meta-builtin/内置/类型型", &type_t_cell },
  { "meta-builtin/内置/任意型", &any_t_cell },
  { "meta-builtin/内置/整数型", &int_t_cell },
  { "meta-builtin/内置/浮点型", &float_t_cell },
  { "meta-builtin/内置/文本型", &text_t_cell },
  { "meta-builtin/内置/符号型", &symbol_t_cell },
  { "meta-builtin/内置/真假型", &bool_t_cell },
  { "meta-builtin/内置/空值型", &void_t_cell },
  { "meta-builtin/内置/文件型", &file_t_cell },
  { "meta-builtin/内置/列表型", (void *) x_list_t },
  { "meta-builtin/内置/数组型", (void *) x_array_t },
  { "meta-builtin/内置/集合型", (void *) x_set_t },
  { "meta-builtin/内置/散列型", (void *) x_hash_t },
  { "meta-builtin/内置/序对型", (void *) x_pair_t },

  // value

  { "meta-builtin/内置/为原子", (void *) x_is_atom },
  { "meta-builtin/内置/相同", (void *) x_same },
  { "meta-builtin/内置/相等", (void *) x_equal },
  { "meta-builtin/内置/呈现", (void *) x_format },
  { "meta-builtin/内置/散列码", (void *) x_hash_code },
  { "meta-builtin/内置/全序比较", (void *) x_total_compare },

  // file

  { "meta-builtin/内置/打开输入文件", (void *) x_open_input_file },
  { "meta-builtin/内置/打开输出文件", (void *) x_open_output_file },
  { "meta-builtin/内置/文件关闭", (void *) x_file_close },
  { "meta-builtin/内置/文件读", (void *) x_file_read },
  { "meta-builtin/内置/文件写", (void *) x_file_write },
  { "meta-builtin/内置/文件写行", (void *) x_file_writeln },
  { "meta-builtin/内置/打印", (void *) x_print },
  { "meta-builtin/内置/打印行", (void *) x_println },

  // path

  { "meta-builtin/内置/路径文件名", (void *) x_path_file_name },
  { "meta-builtin/内置/路径目录名", (void *) x_path_directory_name },
  { "meta-builtin/内置/路径扩展名", (void *) x_path_extension },
  { "meta-builtin/内置/路径主干", (void *) x_path_stem },
  { "meta-builtin/内置/路径为绝对", (void *) x_path_is_absolute },
  { "meta-builtin/内置/路径为相对", (void *) x_path_is_relative },
  { "meta-builtin/内置/路径连接", (void *) x_path_join },
  { "meta-builtin/内置/路径规范化", (void *) x_path_normalize },
  { "meta-builtin/内置/路径相对", (void *) x_path_relative },
  { "meta-builtin/内置/路径相对于当前目录", (void *) x_path_relative_to_cwd },
  { "meta-builtin/内置/路径解析", (void *) x_path_resolve },

  // random

  { "meta-builtin/内置/随机整数", (void *) x_random_int },
  { "meta-builtin/内置/随机浮点", (void *) x_random_float },

  // symbol

  { "meta-builtin/内置/为符号", (void *) x_is_symbol },
  { "meta-builtin/内置/符号长度", (void *) x_symbol_length },
  { "meta-builtin/内置/符号转文本", (void *) x_symbol_to_text },
  { "meta-builtin/内置/符号追加", (void *) x_symbol_append },
  { "meta-builtin/内置/符号拼接", (void *) x_symbol_concat },

  // string

  { "meta-builtin/内置/为文本", (void *) x_is_text },
  { "meta-builtin/内置/文本长度", (void *) x_text_length },
  { "meta-builtin/内置/文本为空", (void *) x_text_is_empty },
  { "meta-builtin/内置/文本为空白", (void *) x_text_is_blank },
  { "meta-builtin/内置/文本截取", (void *) x_text_slice },
  { "meta-builtin/内置/文本追加", (void *) x_text_append },
  { "meta-builtin/内置/文本拼接", (void *) x_text_concat },
  { "meta-builtin/内置/文本字典序比较", (void *) x_text_compare_lexical },
  { "meta-builtin/内置/文本转符号", (void *) x_text_to_symbol },
  { "meta-builtin/内置/文本字符", (void *) x_text_chars },
  { "meta-builtin/内置/文本行", (void *) x_text_lines },
  { "meta-builtin/内置/文本分割", (void *) x_text_split },
  { "meta-builtin/内置/文本连接", (void *) x_text_join },
  { "meta-builtin/内置/文本替换", (void *) x_text_replace },
  { "meta-builtin/内置/文本为前缀", (void *) x_text_is_prefix },
  { "meta-builtin/内置/文本为后缀", (void *) x_text_is_suffix },
  { "meta-builtin/内置/文本转大写", (void *) x_text_to_upper_case },
  { "meta-builtin/内置/文本转小写", (void *) x_text_to_lower_case },
  { "meta-builtin/内置/文本取码点", (void *) x_text_get_code_point },
  { "meta-builtin/内置/文本含于", (void *) x_text_include },
  { "meta-builtin/内置/文本查找索引", (void *) x_text_find_index },
  { "meta-builtin/内置/文本修剪左端", (void *) x_text_trim_left },
  { "meta-builtin/内置/文本修剪右端", (void *) x_text_trim_right },
  { "meta-builtin/内置/文本修剪首端", (void *) x_text_trim_start },
  { "meta-builtin/内置/文本修剪尾端", (void *) x_text_trim_end },
  { "meta-builtin/内置/文本修剪", (void *) x_text_trim },
  { "meta-builtin/内置/文本为整数", (void *) x_text_is_int },
  { "meta-builtin/内置/文本为浮点", (void *) x_text_is_float },
  { "meta-builtin/内置/文本转整数", (void *) x_text_to_int },
  { "meta-builtin/内置/文本转浮点", (void *) x_text_to_float },

  // list

  { "meta-builtin/内置/空列表", &null_cell },
  { "meta-builtin/内置/为列表", (void *) x_is_any_list },
  { "meta-builtin/内置/首", (void *) x_car },
  { "meta-builtin/内置/余", (void *) x_cdr },
  { "meta-builtin/内置/添", (void *) x_cons },

  // array

  { "meta-builtin/内置/作数组", (void *) x_make_array },
  { "meta-builtin/内置/为数组", (void *) x_is_any_array },
  { "meta-builtin/内置/数组复制", (void *) x_array_copy },
  { "meta-builtin/内置/数组长度", (void *) x_array_length },
  { "meta-builtin/内置/数组为空", (void *) x_array_is_empty },
  { "meta-builtin/内置/数组末出", (void *) x_array_pop_mut },
  { "meta-builtin/内置/数组末入", (void *) x_array_push_mut },
  { "meta-builtin/内置/数组首出", (void *) x_array_pop_front_mut },
  { "meta-builtin/内置/数组首入", (void *) x_array_push_front_mut },
  { "meta-builtin/内置/数组取", (void *) x_array_get },
  { "meta-builtin/内置/数组存", (void *) x_array_put_mut },
  { "meta-builtin/内置/数组反转", (void *) x_array_reverse_mut },
  { "meta-builtin/内置/数组转列表", (void *) x_array_to_list },
  { "meta-builtin/内置/列表转数组", (void *) x_list_to_array },

  // pair

  { "meta-builtin/内置/作序对", (void *) x_make_pair },
  { "meta-builtin/内置/序对前项", (void *) x_pair_first },
  { "meta-builtin/内置/序对后项", (void *) x_pair_second },
  { "meta-builtin/内置/序对存前项", (void *) x_pair_put_first },
  { "meta-builtin/内置/序对存后项", (void *) x_pair_put_second },

  // hash

  { "meta-builtin/内置/作散列", (void *) x_make_hash },
  { "meta-builtin/内置/为散列", (void *) x_is_any_hash },
  { "meta-builtin/内置/散列复制", (void *) x_hash_copy },
  { "meta-builtin/内置/散列长度", (void *) x_hash_length },
  { "meta-builtin/内置/散列为空", (void *) x_hash_is_empty },
  { "meta-builtin/内置/散列取", (void *) x_hash_get },
  { "meta-builtin/内置/散列有", (void *) x_hash_has },
  { "meta-builtin/内置/散列存", (void *) x_hash_put_mut },
  { "meta-builtin/内置/散列复制存", (void *) x_hash_put },
  { "meta-builtin/内置/散列删除", (void *) x_hash_delete_mut },
  { "meta-builtin/内置/散列键", (void *) x_hash_keys },
  { "meta-builtin/内置/散列值", (void *) x_hash_values },
  { "meta-builtin/内置/散列条目", (void *) x_hash_entries },

  // set

  { "meta-builtin/内置/作集合", (void *) x_make_set },
  { "meta-builtin/内置/为集合", (void *) x_is_any_set },
  { "meta-builtin/内置/集合复制", (void *) x_set_copy },
  { "meta-builtin/内置/集合大小", (void *) x_set_size },
  { "meta-builtin/内置/集合为空", (void *) x_set_is_empty },
  { "meta-builtin/内置/集合属于", (void *) x_set_member },
  { "meta-builtin/内置/集合添加", (void *) x_set_add_mut },
  { "meta-builtin/内置/集合复制添加", (void *) x_set_add },
  { "meta-builtin/内置/集合删除", (void *) x_set_delete_mut },
  { "meta-builtin/内置/集合复制删除", (void *) x_set_delete },
  { "meta-builtin/内置/集合清空", (void *) x_set_clear_mut },
  { "meta-builtin/内置/集合并", (void *) x_set_union },
  { "meta-builtin/内置/集合交", (void *) x_set_inter },
  { "meta-builtin/内置/集合差", (void *) x_set_difference },
  { "meta-builtin/内置/集合含于", (void *) x_set_include },
  { "meta-builtin/内置/集合不交", (void *) x_set_disjoint },
  { "meta-builtin/内置/集合转列表", (void *) x_set_to_list },

  // assert

  { "meta-builtin/内置/断言", (void *) x_assert },
  { "meta-builtin/内置/断言非", (void *) x_assert_not },
  { "meta-builtin/内置/断言相等", (void *) x_assert_equal },
  { "meta-builtin/内置/断言不等", (void *) x_assert_not_equal },
  { "meta-builtin/内置/定位断言", (void *) x_assert_with_location },
  { "meta-builtin/内置/定位断言非", (void *) x_assert_not_with_location },
  { "meta-builtin/内置/定位断言相等", (void *) x_assert_equal_with_location },
  { "meta-builtin/内置/定位断言不等", (void *) x_assert_not_equal_with_location },

  // error

  { "meta-builtin/内置/报错", (void *) x_error },
  { "meta-builtin/内置/定位报错", (void *) x_error_with_location },

  // sexp

  { "meta-builtin/内置/解析符号算式", (void *) x_parse_sexps_zh },
  { "meta-builtin/内置/呈现为符号算式", (void *) x_format_as_sexp },
  { "meta-builtin/内置/呈现定位消息", (void *) x_format_message_with_location },

  // json

  { "meta-builtin/内置/解析结森", (void *) x_parse_json_zh },
  { "meta-builtin/内置/呈现结森", (void *) x_format_json_zh },

  // fs

  { "meta-builtin/内置/路径存在", (void *) x_path_exists },
  { "meta-builtin/内置/路径为文件", (void *) x_path_is_file },
  { "meta-builtin/内置/路径为目录", (void *) x_path_is_directory },
  { "meta-builtin/内置/路径读", (void *) x_path_read },
  { "meta-builtin/内置/路径写", (void *) x_path_write },
  { "meta-builtin/内置/路径列表", (void *) x_path_list },
  { "meta-builtin/内置/路径递归列表", (void *) x_path_list_recursive },
  { "meta-builtin/内置/路径确保文件", (void *) x_path_ensure_file },
  { "meta-builtin/内置/路径确保目录", (void *) x_path_ensure_directory },
  { "meta-builtin/内置/路径删除文件", (void *) x_path_delete_file },
  { "meta-builtin/内置/路径删除目录", (void *) x_path_delete_directory },
  { "meta-builtin/内置/路径删除", (void *) x_path_delete },
  { "meta-builtin/内置/路径重命名", (void *) x_path_rename },

  // closure
  // - note: zh code calls 作闭包 / 闭包存参 / 闭包取参 directly as
  //   primitives; the x86 compiler itself always generates the en names
  //   (see builtin_en.c), so closure-fn is only registered in en.

  { "meta-builtin/内置/作闭包", (void *) x86_make_closure },
  { "meta-builtin/内置/闭包存参", (void *) x86_closure_put_arg_mut },
  { "meta-builtin/内置/闭包取参", (void *) x86_closure_arg },

  // process

  { "meta-builtin/内置/退出", (void *) x_exit },
  { "meta-builtin/内置/当前目录", (void *) x_current_directory },
  { "meta-builtin/内置/当前命令行", (void *) x_current_command_line },
  { "meta-builtin/内置/当前完整命令行", (void *) x_current_full_command_line },
  { "meta-builtin/内置/当前标准输出文件", (void *) x_current_stdout_file },
  { "meta-builtin/内置/当前标准错误文件", (void *) x_current_stderr_file },
};

#pragma GCC diagnostic pop

const size_t builtin_symbols_zh_count =
  sizeof(builtin_symbols_zh) / sizeof(builtin_symbols_zh[0]);