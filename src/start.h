#pragma once
#include "./types.h"

typedef enum MMAP_Entry_Kind {
    MMAP_ENTRY_INVALID              = 0,
    MMAP_ENTRY_AVAILABLE            = 1,
    MMAP_ENTRY_RESERVED             = 2,
    MMAP_ENTRY_ACPI_RECLAIMABLE     = 3,
    MMAP_ENTRY_NON_VOLATILE_STORAGE = 4,
    MMAP_ENTRY_BAD_RAM              = 5,
} MMAP_Entry_Kind;

typedef struct MMAP_Entry {
    Flat64 paddr;
    u64 size;
    MMAP_Entry_Kind kind;
} MMAP_Entry;

typedef struct MMAP_Entries {
    i32 count;
    MMAP_Entry items[256];
} MMAP_Entries;

c_string cmdline(void);

c_string bootloader_name(void);

MMAP_Entries mmap_entries(void);

c_string mmap_entry_type_name(MMAP_Entry_Kind kind);
