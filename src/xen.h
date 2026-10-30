#pragma once
#include "types.h"

#define XEN_HVM_START_MAGIC 0x336ec578
typedef struct Xen_HVM_Start_Info {
    u32 magic;
    u32 version;
    u32 flags; // bit 0 set means Sieve/Console layout info is valid
    u32 module_count;
    Flat64 modlist_paddr; // array of struct hvm_modlist_entry
    Flat64 cmdline_paddr; // c_string

    Flat64 rsdp_paddr;   // ACPI_RSDP
    Flat64 memmap_paddr; // Xen_MMAP_Entry
    u32 memmap_count;
    u32 reserved;
} Xen_HVM_Start_Info;

#define XEN_HVM_MMAP_TYPE_INVALID   0
#define XEN_HVM_MMAP_TYPE_RAM       1
#define XEN_HVM_MMAP_TYPE_RESERVED  2
#define XEN_HVM_MMAP_TYPE_ACPI      3
#define XEN_HVM_MMAP_TYPE_NVS       4
#define XEN_HVM_MMAP_TYPE_UNUSABLE  5
#define XEN_HVM_MMAP_TYPE_DISABLED  6
#define XEN_HVM_MMAP_TYPE_PMEM      7
typedef struct Xen_MMAP_Entry {
    Flat64 paddr;
    u64 size;
    u32 type;
    u32 reserved;
} Xen_MMAP_Entry;
static_assert(sizeof(Xen_MMAP_Entry) == 24);

typedef struct {
    i32 count;
    Xen_MMAP_Entry items[128];
} Xen_MMAP_Entries;

Xen_HVM_Start_Info const* xen_hvm_start_info(void);
void xen_hvm_init(u32 magic, Xen_HVM_Start_Info const*);

Xen_MMAP_Entries xen_hvm_mmap_entries(void);
