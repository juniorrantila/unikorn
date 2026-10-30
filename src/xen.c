#include "./xen.h"
#include "./verify.h"
#include "./types.h"

static Xen_HVM_Start_Info const* xen;
void xen_hvm_init(u32 magic, Xen_HVM_Start_Info const* x)
{
    (void)magic;
    if (!C_VERIFYS(xen == nullptr, "xen has already been initialized")) return;
    VERIFY(x->version >= 1);
    xen = x;
}

Xen_HVM_Start_Info const* xen_hvm_start_info(void)
{
    Xen_HVM_Start_Info const* x = xen;
    VERIFYS(x, "xen_hvm_init has not been called yet");
    return x;
}

Xen_MMAP_Entries xen_hvm_mmap_entries(void)
{
    Xen_MMAP_Entries result = {0};

    Xen_HVM_Start_Info const* info = xen_hvm_start_info();
    Xen_MMAP_Entry* entries = flat_cast(info->memmap_paddr);
    u32 count = info->memmap_count;
    for (u32 i = 0; i < count; i++) {
        if (!C_VERIFY(i < ARRAY_SSIZE(result.items)))
            break;
        if (entries[i].type == 0)
            continue;
        result.items[result.count++] = entries[i];
    }

    return result;
}
