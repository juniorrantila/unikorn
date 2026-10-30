#include "./types.h"
#include "./verify.h"

void* flat32_cast(Flat32 ptr)
{
    Flat32 other = (Flat32)(uptr)ptr;
    VERIFYS(other == ptr, "flat pointer truncation detected");
    return (void*)(uptr)ptr;
}

void* flat64_cast(Flat64 ptr)
{
    Flat64 other = (Flat64)(uptr)ptr;
    VERIFYS(other == ptr, "flat pointer truncation detected");
    return (void*)(uptr)ptr;
}
