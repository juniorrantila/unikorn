.code32
.global _start

// .section .multiboot, "a"
// .align 4
// .long 0x1BADB002         // Magic number for Multiboot 1
// .long 0x00000003         // Flags: require page alignment + memory info
// .long -(0x1BADB002 + 0x00000003) // Checksum

.section .note.Xen.pvh, "a"
.align 4
.long 4
.long 4
.long 18
.ascii "Xen\0"
.long _start

.section .text
_start:
    mov $_stack_top, %esp
    push %ebx
    push %eax

    // Enable SSE
    mov %cr0, %eax
    and $0xFFFFFFFB, %eax
    or  $0x00000002, %eax
    mov %eax, %cr0
    mov %cr4, %eax
    or  $0x00000600, %eax
    mov %eax, %cr4

    call kernel_start
    cli
1:  hlt
    jmp 1b
