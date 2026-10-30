#include "./start.h"
#include "./kernel.h"
#include "./multiboot.h"
#include "./xen.h"
#include "./types.h"

static MMAP_Entries from_multiboots(void);
static MMAP_Entries from_xens(void);

static MMAP_Entry from_multiboot(Multiboot_MMAP_Entry);
static MMAP_Entry from_xen(Xen_MMAP_Entry);

c_string cmdline(void)
{
    switch (kernel.boot) {
    case BOOT_UNKNOWN: return "";
    case BOOT_MULTIBOOT: return flat_cast(multiboot_info()->cmdline);
    case BOOT_XEN_PVH: return flat_cast(xen_hvm_start_info()->cmdline_paddr);
    }
}

c_string bootloader_name(void)
{
    switch (kernel.boot) {
    case BOOT_UNKNOWN: return "unknown";
    case BOOT_MULTIBOOT: return multiboot_bootloader_name();
    case BOOT_XEN_PVH: return "xen";
    }
}

MMAP_Entries mmap_entries(void)
{
    switch (kernel.boot) {
    case BOOT_UNKNOWN:
        return (MMAP_Entries){};
    case BOOT_MULTIBOOT:
        return from_multiboots();
    case BOOT_XEN_PVH:
        return from_xens();
    }
}

static MMAP_Entries from_multiboots(void)
{
    MMAP_Entries result = {};
    Multiboot_MMAP_Entries entries = multiboot_mmap_entries();
    static_assert(ARRAY_SSIZE(result.items) >= ARRAY_SSIZE(entries.items));

    for (i32 i = 0; i < entries.count; i++) {
        result.items[result.count++] = from_multiboot(entries.items[i]);
    }

    return result;
}

static MMAP_Entries from_xens(void)
{
    MMAP_Entries result = {};
    Xen_MMAP_Entries entries = xen_hvm_mmap_entries();
    static_assert(ARRAY_SSIZE(result.items) >= ARRAY_SSIZE(entries.items));

    for (i32 i = 0; i < entries.count; i++) {
        result.items[result.count++] = from_xen(entries.items[i]);
    }

    return result;
}

static MMAP_Entry from_multiboot(Multiboot_MMAP_Entry e)
{
    u32 type = MMAP_ENTRY_BAD_RAM;
    switch (e.type) {
    case MULTIBOOT_MMAP_TYPE_INVALID:
        type = MMAP_ENTRY_INVALID;
        break;
    case MULTIBOOT_MMAP_TYPE_AVAILABLE:
        type = MMAP_ENTRY_AVAILABLE;
        break;
    case MULTIBOOT_MMAP_TYPE_RESERVED:
        type = MMAP_ENTRY_RESERVED;
        break;
    case MULTIBOOT_MMAP_TYPE_ACPI_RECLAIMABLE:
        type = MMAP_ENTRY_ACPI_RECLAIMABLE;
        break;
    case MULTIBOOT_MMAP_TYPE_NON_VOLATILE_STORAGE:
        type = MMAP_ENTRY_NON_VOLATILE_STORAGE;
        break;
    case MULTIBOOT_MMAP_TYPE_BAD_RAM:
        type = MMAP_ENTRY_BAD_RAM;
        break;
    }

    return (MMAP_Entry){
        .paddr = e.base_addr,
        .size = e.length,
        .kind = type,
    };
}

static MMAP_Entry from_xen(Xen_MMAP_Entry e)
{
    u32 type = MMAP_ENTRY_BAD_RAM;
    switch (e.type) {
    case XEN_HVM_MMAP_TYPE_INVALID:
        type = MMAP_ENTRY_INVALID;
        break;
    case XEN_HVM_MMAP_TYPE_PMEM:
    case XEN_HVM_MMAP_TYPE_RAM:
        type = MMAP_ENTRY_AVAILABLE;
        break;
    case XEN_HVM_MMAP_TYPE_RESERVED:
        type = MMAP_ENTRY_RESERVED;
        break;
    case XEN_HVM_MMAP_TYPE_ACPI:
        type = MMAP_ENTRY_ACPI_RECLAIMABLE;
        break;
    case XEN_HVM_MMAP_TYPE_NVS:
        type = MMAP_ENTRY_NON_VOLATILE_STORAGE;
        break;
    case XEN_HVM_MMAP_TYPE_UNUSABLE:
    case XEN_HVM_MMAP_TYPE_DISABLED:
        type = MMAP_ENTRY_BAD_RAM;
        break;
    }

    return (MMAP_Entry){
        .paddr = e.paddr,
        .size = e.size,
        .kind = type,
    };
}

c_string mmap_entry_type_name(MMAP_Entry_Kind kind)
{
    switch (kind) {
    case MMAP_ENTRY_INVALID: return "invalid";
    case MMAP_ENTRY_AVAILABLE: return "available";
    case MMAP_ENTRY_RESERVED: return "reserved";
    case MMAP_ENTRY_ACPI_RECLAIMABLE: return "acpi reclaimable";
    case MMAP_ENTRY_NON_VOLATILE_STORAGE: return "non-volatile storage";
    case MMAP_ENTRY_BAD_RAM: return "bad ram";
    }
    return "unknown";
}
