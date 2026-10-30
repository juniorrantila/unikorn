#include "./qemu.h"
#include "./types.h"

void qemu_shutdown(void)
{
    // Trigger triple fault
    u64 volatile zero_idt = 0;
    __asm__ __volatile__(
        "lidt %0\n\t"
        "int3"
        :
        : "m"(zero_idt)
    );
}
