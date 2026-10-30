#include "./kernel.h"
#include "./io.h"
#include "./multiboot.h"
#include "./heap.h"
#include "./x86.h"
#include "./qemu.h"
#include "./virtio.h"
#include "./memutil.h"
#include "./verify.h"
#include "./start.h"
#include "./xen.h"

Kernel kernel;

void kernel_main(void)
{
    xprintk("bootloader: %s", bootloader_name());

    xprintk("scanning mmap entries");
    MMAP_Entries mmap = mmap_entries();
    for (i32 i = 0; i < mmap.count; i++) {
        MMAP_Entry entry = mmap.items[i];
        xprintk("memory(%u)@%08llx:%s \"%s\"", entry.kind, entry.paddr, memory_size(entry.size), mmap_entry_type_name(entry.kind));
    }

    xprintk("scanning virtio devices");
    VirtIO_Devices virtio_devices = virtio_scan_devices();
    kernel.devices.count++; // Nil device
    for (i32 i = 0; i < virtio_devices.count; i++) {
        VirtIO_MMIO volatile* device = virtio_devices.items[i];
        u32 id = device->device_id;
        xprintk("device(%u)@%p:%u \"%s\"", id, device, device->version, virtio_device_type_name(id));
        VirtIO_Device_ID device_idx = kernel.devices.count++;
        kernel.devices.items[device_idx] = device;
        switch (id) {
        case VIRTIO_DEVICE_ENTROPY_SOURCE: 
            kernel.entropy_source = device_idx;
            break;
        case VIRTIO_DEVICE_CONSOLE: 
            kernel.console_device = device_idx;
            break;
        case VIRTIO_DEVICE_NETWORK: 
            kernel.network_device = device_idx;
            break;
        case VIRTIO_DEVICE_9P_TRANSPORT: 
            kernel.p9_transport = device_idx;
            break;
        }
    }

    if (kernel.entropy_source) xprintk("entropy source:      %u", kernel.entropy_source);
    else xprintk("entropy source:      none");
    if (kernel.console_device) xprintk("console device:      %u", kernel.console_device);
    else xprintk("console device:      none");
    if (kernel.network_device) xprintk("network device:      %u", kernel.network_device);
    else xprintk("network device:      none");
    if (kernel.p9_transport) xprintk("9p transport device: %u", kernel.p9_transport);
    else xprintk("9p transport device: none");
}

[[noreturn]]
void kernel_start(u32 magic, void* ptr)
{
    xprintk("\nHello, World");
    VERIFY(ptr != nullptr, "eeh, we can not proceed");

    kernel.boot = BOOT_UNKNOWN;
    if (magic == XEN_HVM_START_MAGIC) {
        kernel.boot = BOOT_XEN_PVH;
    }
    if (magic == MULTIBOOT_MAGIC) {
        kernel.boot = BOOT_MULTIBOOT;
        if ((*(u32*)ptr) == XEN_HVM_START_MAGIC) {
            kernel.boot = BOOT_XEN_PVH;
        }
    }

    switch (kernel.boot) {
    case BOOT_UNKNOWN:
        break;
    case BOOT_XEN_PVH:
        xen_hvm_init(magic, ptr);
        break;
    case BOOT_MULTIBOOT:
        multiboot_init(magic, ptr);
        break;
    }

    xprintk("bss size:  %s", memory_size(bss_size()));
    xprintk("heap size: %s", memory_size(heap_size()));

    kernel_main();

    qemu_shutdown();
    halt();
}
