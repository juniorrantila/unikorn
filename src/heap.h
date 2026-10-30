#pragma once
#include "./types.h"

u64 bss_size(void);
u64 heap_used(void);
u64 heap_size(void);

void* heap_alloc(u32 size, u32 align);
void* heap_alloc_no_zero(u32 size, u32 align);
