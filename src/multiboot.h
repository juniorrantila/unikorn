#pragma once
#include "./types.h"

#define MULTIBOOT_MAGIC 0x2BADB002
typedef struct [[gnu::packed]] Multiboot_Info {
    u32 flags;
    u32 mem_lower;
    u32 mem_upper;
    u32 boot_device;
    Flat32 cmdline;
    u32 mods_count;
    Flat32 mods_addr;

    // syms (for ELF; present if flags:5 is set)
    u32 syms_num;
    u32 syms_size;
    Flat32 syms_addr;
    u32 syms_shndex;

    // memory map (if flags:6 is set)
    u32 mmap_length;
    Flat32 mmap_addr;

    // disk drives (flags:7)
    u32 drives_length;
    Flat32 drives_addr;

    Flat32 config_table; // (if flags:8 set)
    Flat32 boot_loader_name;  // (if flags:9 set)
    Flat32 apm_table; // (if flags:10 set)

    // VBE info, present if flags:11 is set
    Flat32 vbe_control_info;
    Flat32 vbe_mode_info;
    u16 vbe_mode;
    u16 vbe_interface_seg;
    u16 vbe_interface_off;
    u16 vbe_interface_len;

    // framebuffer (flags:12)
    Flat64 framebuffer_addr;
    u32 framebuffer_pitch;
    u32 framebuffer_width;
    u32 framebuffer_height;
    u8 framebuffer_bpp;
    u8 framebuffer_type; // 0 = indexed, 1 = direct color, 2 = text mode
} Multiboot_Info;

#define MULTIBOOT_MMAP_TYPE_INVALID                 0
#define MULTIBOOT_MMAP_TYPE_AVAILABLE               1
#define MULTIBOOT_MMAP_TYPE_RESERVED                2
#define MULTIBOOT_MMAP_TYPE_ACPI_RECLAIMABLE        3
#define MULTIBOOT_MMAP_TYPE_NON_VOLATILE_STORAGE    4
#define MULTIBOOT_MMAP_TYPE_BAD_RAM                 5

typedef struct [[gnu::packed]] Multiboot_MMAP_Entry {
    u32 size;          /* Size of entry structure minus this field */
    Flat64 base_addr;
    u64 length;
    u32 type;          /* 1 = Usable RAM, 2 = Reserved, etc. */
} Multiboot_MMAP_Entry;

typedef struct Multiboot_MMAP_Entries {
    i32 count;
    Multiboot_MMAP_Entry items[256];
} Multiboot_MMAP_Entries;

void multiboot_init(u32 magic, Multiboot_Info const*);
Multiboot_Info const* multiboot_info();

c_string multiboot_bootloader_name(void);
Multiboot_MMAP_Entries multiboot_mmap_entries(void);
