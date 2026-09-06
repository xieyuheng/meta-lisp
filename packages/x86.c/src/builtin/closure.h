#pragma once

value_t x86_make_closure(value_t fn_val, value_t size_val);
value_t x86_closure_put_arg_mut(value_t index_val, value_t value, value_t closure_val);
value_t x86_closure_arg(value_t index_val, value_t closure_val);
value_t x86_closure_fn(value_t closure_val);