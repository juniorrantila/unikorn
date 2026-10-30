#pragma once
#include "./types.h"

[[gnu::format(printf, 5, 6)]]
void __verify_failure(c_string file, i32 file_len, i32 line, c_string expr, c_string fmt, ...);

[[gnu::format(printf, 4, 5)]]
void __fixme_failure(c_string file, i32 file_len, i32 line, c_string fmt, ...);

#define VERIFY(expr, ...) ({ if (!(expr)) { __verify_failure(__FILE__, sizeof(__FILE__) - 1, __LINE__, #expr, 0); __builtin_trap(); } })
#define C_VERIFY(expr, ...) ({ bool __result = (expr); if (!__result) { __verify_failure(__FILE__, sizeof(__FILE__) - 1, __LINE__, #expr, 0); } __result; })

#define VERIFYS(expr, fmt, ...) ({ if (!(expr)) { __verify_failure(__FILE__, sizeof(__FILE__) - 1, __LINE__, #expr, fmt, ##__VA_ARGS__); __builtin_trap(); } })
#define C_VERIFYS(expr, fmt, ...) ({ bool __result = (expr); if (!__result) { __verify_failure(__FILE__, sizeof(__FILE__) - 1, __LINE__, #expr, fmt, ##__VA_ARGS__); } __result; })

#define FIXME(fmt, ...) __fixme_failure(__FILE__, sizeof(__FILE__) - 1, __LINE__, fmt, ##__VA_ARGS__)
#define FIXME_ONCE(fmt, ...) ({ static bool __once; if (!__once) { __fixme_failure(__FILE__, sizeof(__FILE__) - 1, __LINE__, fmt, ##__VA_ARGS__); __once = true; } })
