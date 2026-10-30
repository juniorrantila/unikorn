#include "./arena.h"
#include "./virtio.h"

typedef enum {
    BOOT_UNKNOWN   = 0,
    BOOT_MULTIBOOT = 1,
    BOOT_XEN_PVH   = 2,
} Boot_Mode;

typedef struct Kernel {
    Boot_Mode boot;
    Arena temporary_arena;
    VirtIO_Devices devices;
    VirtIO_Device_ID entropy_source;
    VirtIO_Device_ID p9_transport;
    VirtIO_Device_ID network_device;
    VirtIO_Device_ID console_device;
} Kernel;

extern Kernel kernel;
