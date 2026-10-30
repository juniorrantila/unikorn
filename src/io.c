#include "./io.h"
#include "./serial.h"
#include "./x86.h"
#include "./kernel.h"
#include "./verify.h"

#define STB_SPRINTF_IMPLEMENTATION
#define STB_SPRINTF_STATIC
#define STB_SPRINTF_NOFLOAT
#define STB_SPRINTF_NOUNALIGNED
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#include "./stb_sprintf.h"
#pragma clang diagnostic pop

static char* callback(char const* buf, void* user, i32 len);

[[noreturn]]
[[gnu::format(printf, 1, 0)]]
void panic(c_string fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vxprintf(fmt, args);
    va_end(args);
    serial_put('\n');
    halt();
}

[[gnu::format(printf, 1, 0)]]
void vxprintf(char const* fmt, va_list args)
{
    char buf[STB_SPRINTF_MIN];
    stbsp_vsprintfcb(callback, 0, buf, fmt, args);
}

[[gnu::format(printf, 1, 2)]]
void xprintk(char const* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vxprintf(fmt, args);
    va_end(args);
    serial_put('\n');
}

[[gnu::format(printf, 1, 2)]]
void xprintf(char const* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vxprintf(fmt, args);
    va_end(args);
}

[[gnu::format(printf, 1, 2)]]
c_string tprintf(c_string fmt, ...)
{
    va_list args;
    va_list args2;
    va_start(args, fmt);
    va_copy(args2, args);

    i32 len = stbsp_vsnprintf(0, 0, fmt, args);
    if (!C_VERIFY(len >= 0)) return 0;
    if (len == 0) return "";
    char* buf = arena_push(&kernel.temporary_arena, len + 1, 1);
    i32 len2 = stbsp_vsnprintf(buf, len + 1, fmt, args);
    VERIFY(len == len2);

    return buf;
}

static char* callback(char const* buf, void* user, i32 len)
{
    (void)user;
    serial_write(buf, len);
    return (char*)buf;
}
