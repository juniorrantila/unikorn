#include "./arena.h"
#include "./verify.h"
#include "./memutil.h"
#include "./heap.h"
#include "./io.h"

[[nodiscard]]
static bool init_if_needed(Arena*);

void arena_init(Arena* a, u8* memory, u64 size)
{
    a->base = (Flat64)memory;
    a->head = (Flat64)memory;
    a->end = (Flat64)(memory + size);
}

Flat64 arena_mark(Arena const* a)
{
    return a->head;
}

void arena_reset(Arena* a, Flat64 location)
{
    VERIFY(location >= a->base);
    VERIFY(location <= a->end);
    a->head = location;
}

void* arena_push_no_zero(Arena* a, u32 size, u32 align)
{
    if (!init_if_needed(a)) return 0;
    u8* ptr = flat_cast(a->base);
    ptr = ALIGN_UP(ptr, align);
    Flat64 end = ((Flat64)ptr) + size;
    if (end < a->base) return 0;
    if (end >= a->end) return 0;
    a->head = end;
    return ptr;
}

void* arena_push(Arena* a, u32 size, u32 align)
{
    void* memory = arena_push_no_zero(a, size, align);
    if (memory) MEMSET(memory, 0, size);
    return memory;
}

[[nodiscard]]
static bool init_if_needed(Arena* a)
{
    if (a->base) return true;
    u32 size = 64 * Ki;
    void* memory = heap_alloc_no_zero(size, 16);
    if (!memory) {
        xprintk("could not allocate arena");
        return false;
    }
    arena_init(a, memory, size);
    return true;
}
