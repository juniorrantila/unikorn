#pragma once
#include "./types.h"

[[maybe_unused]]
static inline u32 mmio_read32(Flat64 ptr)
{
    return *(u32 volatile*)flat_cast(ptr);
}
