#pragma once
#include "./types.h"

typedef struct Arena {
    Flat64 base;
    Flat64 head;
    Flat64 end;
} Arena;

void arena_init(Arena*, u8* memory, u64 size);
Flat64 arena_mark(Arena const*);
void      arena_reset(Arena*, Flat64);

void* arena_push(Arena*, u32 size, u32 align);
void* arena_push_no_zero(Arena*, u32 size, u32 align);
#define ARENA_PUSH(a, T) arena_push((a), sizeof(T), alignof(T))
