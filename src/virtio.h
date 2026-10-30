#pragma once
#include "./types.h"

#define VIRTIO_DEVICE_INVALID                            0
#define VIRTIO_DEVICE_NETWORK                            1
#define VIRTIO_DEVICE_BLOCK                              2
#define VIRTIO_DEVICE_CONSOLE                            3
#define VIRTIO_DEVICE_ENTROPY_SOURCE                     4
#define VIRTIO_DEVICE_MEMORY_BALLOONING_TRADITIONAL      5
#define VIRTIO_DEVICE_IOMEMORY                           6
#define VIRTIO_DEVICE_RPMSG                              7
#define VIRTIO_DEVICE_SCSI_HOST                          8
#define VIRTIO_DEVICE_9P_TRANSPORT                       9
#define VIRTIO_DEVICE_MAC80211_WLAN                      10
#define VIRTIO_DEVICE_RPROC_SERIAL                       11
#define VIRTIO_DEVICE_VIRTIO_CAIF                        12
#define VIRTIO_DEVICE_MEMORY_BALLOON                     13
#define VIRTIO_DEVICE_GPU_DEVICE                         16
#define VIRTIO_DEVICE_REAL_TIME_CLOCK                    17
#define VIRTIO_DEVICE_INPUT_DEVICE                       18
#define VIRTIO_DEVICE_SOCKET                             19
#define VIRTIO_DEVICE_CRYPTO                             20
#define VIRTIO_DEVICE_SIGNAL_DISTRIBUTION_MODULE         21
#define VIRTIO_DEVICE_PSTORE                             22
#define VIRTIO_DEVICE_IOMMU                              23
#define VIRTIO_DEVICE_MEMORY                             24
#define VIRTIO_DEVICE_SOUND                              25
#define VIRTIO_DEVICE_FILE_SYSTEM                        26
#define VIRTIO_DEVICE_PMEM                               27
#define VIRTIO_DEVICE_RPMB                               28
#define VIRTIO_DEVICE_MAC80211_HWSIM_WIRELESS_SIMULATION 29
#define VIRTIO_DEVICE_VIDEO_ENCODER                      30
#define VIRTIO_DEVICE_VIDEO_DECODER                      31
#define VIRTIO_DEVICE_SCMI_DEVICE                        32
#define VIRTIO_DEVICE_NITROSECUREMODULE                  33
#define VIRTIO_DEVICE_I2C_ADAPTER                        34
#define VIRTIO_DEVICE_WATCHDOG                           35
#define VIRTIO_DEVICE_CAN                                36
#define VIRTIO_DEVICE_PARAMETER_SERVER                   38
#define VIRTIO_DEVICE_AUDIO_POLICY                       39
#define VIRTIO_DEVICE_BLUETOOTH                          40
#define VIRTIO_DEVICE_GPIO                               41
#define VIRTIO_DEVICE_RDMA                               42
#define VIRTIO_DEVICE_CAMERA                             43
#define VIRTIO_DEVICE_ISM                                44
#define VIRTIO_DEVICE_SPI_CONTROLLER                     45
#define VIRTIO_DEVICE_TEE                                46
#define VIRTIO_DEVICE_CPU_BALLOON                        47
#define VIRTIO_DEVICE_MEDIA                              48
#define VIRTIO_DEVICE_USB_CONTROLLER                     49

#define VIRTIO_DEVICE_COUNT_MAX 8
#define VIRTIO_MMIO_MAGIC 0x74726976
typedef struct [[gnu::packed]] VirtIO_MMIO {
    u32 magic;
    u32 version;
    u32 device_id;
    u32 vendor_id;
    u32 device_features;
    u32 device_features_sel;
    u32 : 32;
    u32 : 32;
    u32 driver_features;
    u32 driver_features_sel;
    u32 guest_page_size;
    u32 : 32;
    u32 queue_sel;
    u32 queue_num_max;
    u32 queue_num;
    u32 queue_align;
    u32 queue_pfn;
    u32 queue_ready;
    u32 : 32;
    u32 : 32;
    u32 queue_notify;
    u32 : 32;
    u32 : 32;
    u32 : 32;
    u32 interrupt_status;
    u32 interrupt_ack;
    u32 : 32;
    u32 : 32;
    u32 status;
    u32 : 32;
    u32 : 32;
    u32 : 32;
    u64 queue_desc;
    u32 : 32;
    u32 : 32;
    u64 queue_avail;
    u32 : 32;
    u32 : 32;
    u64 queue_used;
    u32 : 32;
    u32 shm_sel;
    u64 shm_len;
    u64 shm_base;
    u32 reserved10[15];
    u32 config_generation;
    u8  config[256];
} VirtIO_MMIO;
static_assert(sizeof(VirtIO_MMIO) == 0x200);

c_string virtio_device_type_name(u32 type);

typedef struct VirtIO_Devices {
    i32 count;
    VirtIO_MMIO volatile* items[VIRTIO_DEVICE_COUNT_MAX + 1];
} VirtIO_Devices;

VirtIO_Devices virtio_scan_devices(void);

typedef enum VirtIO_Device_ID : u16 VirtIO_Device_ID;
