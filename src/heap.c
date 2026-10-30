#include "./heap.h"

#include "./arena.h"
#include "./start.h"
#include "./verify.h"

// These are provided by linker
extern void _bss_start;
extern void _bss_end;
extern void _kernel_start;
extern void _kernel_end;

static Arena heap;
static void heap_init_if_needed(void);

u64 bss_size(void)
{
    return (u64)((uptr)&_bss_end - (uptr)&_bss_start);
}

u64 heap_used(void)
{
    return heap.end - heap.head;
}

u64 heap_size(void)
{
    heap_init_if_needed();
    return heap.end - heap.base;
}

void* heap_alloc(u32 size, u32 align)
{
    heap_init_if_needed();
    return arena_push(&heap, size, align);
}

void* heap_alloc_no_zero(u32 size, u32 align)
{
    heap_init_if_needed();
    return arena_push_no_zero(&heap, size, align);
}

static void heap_init_if_needed(void)
{
    if (heap.base) return;

    MMAP_Entries entries = mmap_entries();

    i32 regions = 0;
    MMAP_Entry largest = {0};
    for (i32 i = 0; i < entries.count; i++) {
        MMAP_Entry entry = entries.items[i];
        if (entry.kind != MMAP_ENTRY_AVAILABLE)
            continue;

        if (entry.paddr == 0)
            continue;
        if (entry.paddr >= 0xFFFFFFFF) {
            FIXME_ONCE("support memory over 4G mark");
            continue;
        }

        // This is the entry where the kernel is loaded
        if ((entry.paddr >= (u64)&_kernel_start) && (entry.paddr < (u64)&_kernel_end)) {
            entry.size = entry.paddr - (u64)&_kernel_end + entry.size;
            entry.paddr = (u64)&_kernel_end;
        }

        if (entry.size < largest.size)
            continue;

        largest = entry;
        regions++;
    }

    VERIFYS(largest.kind == MMAP_ENTRY_AVAILABLE, "found %u", largest.kind);
    if (regions > 1) FIXME_ONCE("heap uses only largest contiguous memory region, but should free all available regions, we found %d regions", regions);
    arena_init(&heap, flat_cast(largest.paddr), largest.size);
}
