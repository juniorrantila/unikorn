#pragma once
#include "./types.h"

#define MEMCMP __builtin_memcmp
#define MEMSET __builtin_memset
#define MEMZERO(p) MEMSET((p), 0, sizeof(*(p)))

#define memory_barrier() __asm__ __volatile__("":::"memory")

c_string memory_size(u64 size);
