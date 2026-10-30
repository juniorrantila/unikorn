#include "./memutil.h"
#include "./kernel.h"
#include "./io.h"

c_string memory_size(u64 size)
{
    c_string suffix = "B";
    if (size > 2 * Ki) {
        size /= Ki;
        suffix = "K";
    }
    if (size > 2 * Ki) {
        size /= Ki;
        suffix = "M";
    }
    if (size > 2 * Ki) {
        size /= Ki;
        suffix = "G";
    }
    if (size > 2 * Ki) {
        size /= Ki;
        suffix = "T";
    }
    if (size > 2 * Ki) {
        size /= Ki;
        suffix = "P";
    }
    if (size > 2 * Ki) {
        size /= Ki;
        suffix = "E";
    }

    return tprintf("%llu%s", size, suffix);
}
