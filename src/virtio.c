#include "./virtio.h"

static VirtIO_MMIO volatile* virtio_devices_base(void) { return (VirtIO_MMIO volatile*)0xFEB00000; }

VirtIO_Devices virtio_scan_devices(void)
{

    VirtIO_MMIO volatile* base = virtio_devices_base();
    VirtIO_Devices devices = {};
    for (iptr i = 0; i < ARRAY_SSIZE(devices.items); i++) {
        VirtIO_MMIO volatile* device = base + i;
        if (device->magic != VIRTIO_MMIO_MAGIC)
            continue;
        if (device->device_id == VIRTIO_DEVICE_INVALID)
            continue;
        devices.items[devices.count++] = device;
    }
    return devices;
}

c_string virtio_device_type_name(u32 type)
{
    switch (type) {
    case VIRTIO_DEVICE_INVALID:                            return "invalid";
    case VIRTIO_DEVICE_NETWORK:                            return "network device";
    case VIRTIO_DEVICE_BLOCK:                              return "block device";
    case VIRTIO_DEVICE_CONSOLE:                            return "console";
    case VIRTIO_DEVICE_ENTROPY_SOURCE:                     return "entropy source";
    case VIRTIO_DEVICE_MEMORY_BALLOONING_TRADITIONAL:      return "memory ballooning (traditional)";
    case VIRTIO_DEVICE_IOMEMORY:                           return "ioMemory";
    case VIRTIO_DEVICE_RPMSG:                              return "rpmsg";
    case VIRTIO_DEVICE_SCSI_HOST:                          return "SCSI host";
    case VIRTIO_DEVICE_9P_TRANSPORT:                       return "9P transport";
    case VIRTIO_DEVICE_MAC80211_WLAN:                      return "mac80211 wlan";
    case VIRTIO_DEVICE_RPROC_SERIAL:                       return "rproc serial";
    case VIRTIO_DEVICE_VIRTIO_CAIF:                        return "virtio CAIF";
    case VIRTIO_DEVICE_MEMORY_BALLOON:                     return "memory balloon";
    case VIRTIO_DEVICE_GPU_DEVICE:                         return "GPU device";
    case VIRTIO_DEVICE_REAL_TIME_CLOCK:                    return "RTC (Real Time Clock) device";
    case VIRTIO_DEVICE_INPUT_DEVICE:                       return "Input device";
    case VIRTIO_DEVICE_SOCKET:                             return "Socket device";
    case VIRTIO_DEVICE_CRYPTO:                             return "Crypto device";
    case VIRTIO_DEVICE_SIGNAL_DISTRIBUTION_MODULE:         return "Signal Distribution Module";
    case VIRTIO_DEVICE_PSTORE:                             return "pstore device";
    case VIRTIO_DEVICE_IOMMU:                              return "IOMMU device";
    case VIRTIO_DEVICE_MEMORY:                             return "Memory device";
    case VIRTIO_DEVICE_SOUND:                              return "Sound device";
    case VIRTIO_DEVICE_FILE_SYSTEM:                        return "file system device";
    case VIRTIO_DEVICE_PMEM:                               return "PMEM device";
    case VIRTIO_DEVICE_RPMB:                               return "RPMB device";
    case VIRTIO_DEVICE_MAC80211_HWSIM_WIRELESS_SIMULATION: return "mac80211 hwsim wireless simulation device";
    case VIRTIO_DEVICE_VIDEO_ENCODER:                      return "Video encoder device";
    case VIRTIO_DEVICE_VIDEO_DECODER:                      return "Video decoder device";
    case VIRTIO_DEVICE_SCMI_DEVICE:                        return "SCMI device";
    case VIRTIO_DEVICE_NITROSECUREMODULE:                  return "NitroSecureModule";
    case VIRTIO_DEVICE_I2C_ADAPTER:                        return "I2C adapter";
    case VIRTIO_DEVICE_WATCHDOG:                           return "Watchdog";
    case VIRTIO_DEVICE_CAN:                                return "CAN device";
    case VIRTIO_DEVICE_PARAMETER_SERVER:                   return "Parameter Server";
    case VIRTIO_DEVICE_AUDIO_POLICY:                       return "Audio policy device";
    case VIRTIO_DEVICE_BLUETOOTH:                          return "Bluetooth device";
    case VIRTIO_DEVICE_GPIO:                               return "GPIO device";
    case VIRTIO_DEVICE_RDMA:                               return "RDMA device";
    case VIRTIO_DEVICE_CAMERA:                             return "Camera device";
    case VIRTIO_DEVICE_ISM:                                return "ISM device";
    case VIRTIO_DEVICE_SPI_CONTROLLER:                     return "SPI controller";
    case VIRTIO_DEVICE_TEE:                                return "TEE device";
    case VIRTIO_DEVICE_CPU_BALLOON:                        return "CPU balloon device";
    case VIRTIO_DEVICE_MEDIA:                              return "Media device";
    case VIRTIO_DEVICE_USB_CONTROLLER:                     return "USB controller";
    }
    return "unknown";
}
