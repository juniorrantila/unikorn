#include "./multiboot.h"
#include "./io.h"
#include "./verify.h"

static Multiboot_Info const* multiboot;

void multiboot_init(u32 magic, Multiboot_Info const* m)
{
    VERIFYS(magic == MULTIBOOT_MAGIC, "expected %x, but found %x", MULTIBOOT_MAGIC, magic);
    VERIFYS(m->flags & (1 << 0), "expected multiboot info flag bit 0 to be set");
    if (!C_VERIFYS(multiboot == nullptr, "multiboot has already been initialized")) return;
    multiboot = m;
}

Multiboot_Info const* multiboot_info()
{
    Multiboot_Info const* m = multiboot;
    if (!m) panic("multiboot_init has not been called yet");
    return m;
}

c_string multiboot_bootloader_name(void)
{
    Multiboot_Info const* info = multiboot_info();
    if (!(info->flags & (1 << 9)))
        return "none";
    if (info->boot_loader_name == 0)
        return "unknown";
    return (c_string)(uptr)info->boot_loader_name;
}

Multiboot_MMAP_Entries multiboot_mmap_entries(void)
{
    Multiboot_MMAP_Entries result = {};

    Multiboot_Info const* info = multiboot_info();
    if (!(info->flags & (1 << 6)))
        return result;

    Multiboot_MMAP_Entry* entry = flat_cast(info->mmap_addr);
    Flat_Ptr mmap_end = info->mmap_addr + info->mmap_length;

    while (((Flat_Ptr)entry) < mmap_end) {
        if (entry->type == MULTIBOOT_MMAP_TYPE_INVALID) break;
        if (!C_VERIFYS(result.count < ARRAY_SSIZE(result.items), "too many multiboot mmap entries"))
            break;
        result.items[result.count++] = *entry;
        entry = (Multiboot_MMAP_Entry*)flat_cast(((Flat_Ptr)entry + entry->size + sizeof(entry->size)));
    }

    return result;
}
