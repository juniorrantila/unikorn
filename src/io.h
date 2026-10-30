#pragma once
#include "./types.h"

[[noreturn]]
[[gnu::format(printf, 1, 0)]]
void panic(c_string fmt, ...);

[[gnu::format(printf, 1, 0)]]
void vxprintf(c_string fmt, va_list args);

[[gnu::format(printf, 1, 2)]]
void xprintk(c_string fmt, ...);

[[gnu::format(printf, 1, 2)]]
void xprintf(c_string fmt, ...);

[[gnu::format(printf, 1, 2)]]
c_string tprintf(c_string fmt, ...);
