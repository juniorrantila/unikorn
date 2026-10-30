#pragma once
#include "./types.h"

[[maybe_unused]]
static inline void outb(u16 port, u8 value)
{
    __asm__ __volatile__ ("outb %0, %1" : : "a"(value), "Nd"(port));
}

[[maybe_unused]]
[[noreturn]]
static inline void halt(void)
{
    __asm__ __volatile__ ("cli");
    while (1) __asm__ __volatile__ ("hlt");
}

[[maybe_unused]]
[[noreturn]]
static inline void triple_fault(void)
{
    // Trigger triple fault
    u64 volatile zero_idt = 0;
    __asm__ __volatile__(
        "lidt %0\n\t"
        "int3"
        :
        : "m"(zero_idt)
    );
    halt();
}
