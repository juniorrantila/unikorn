#include "./verify.h"
#include "./io.h"

void __verify_failure(c_string file, i32 file_len, i32 line, c_string expr, c_string fmt, ...)
{
    i32 last_slash = -1;
    for (i32 i = 0; i < file_len; i++) {
        if (file[i] == '/') last_slash = i;
    }
    file += (last_slash + 1);
    xprintf("\033[31mVERIFY\033[0m: %s:%u: %s%s", file, line, expr, fmt ? " " : "\n");
    if (fmt) {
        xprintf("\033[32;1m\"");
        va_list args;
        va_start(args, fmt);
        vxprintf(fmt, args);
        va_end(args);
        xprintf("\"\033[0m\n");
    }
}

void __fixme_failure(c_string file, i32 file_len, i32 line, c_string fmt, ...)
{
    i32 last_slash = -1;
    for (i32 i = 0; i < file_len; i++) {
        if (file[i] == '/') last_slash = i;
    }
    file += (last_slash + 1);
    xprintf("\033[34;1mFIXME\033[0m: %s:%u: ", file, line);
    va_list args;
    va_start(args, fmt);
    vxprintf(fmt, args);
    va_end(args);
    xprintf("\n");
}
