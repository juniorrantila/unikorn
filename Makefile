CC = clang
LD = zig cc

ASMFLAGS = -Wall -Wextra -Werror
ASMFLAGS += -target i386-freestanding-none -ffreestanding
ASMFLAGS += -fcolor-diagnostics

CFLAGS = -Wall -Wextra -Werror -Wshorten-64-to-32 -Wno-elaborated-enum-base
CFLAGS += -target i386-freestanding-none -ffreestanding -mno-red-zone
CFLAGS += -O2
CFLAGS += -std=c2x
CFLAGS += -fcolor-diagnostics

LDFLAGS = -target x86-freestanding-none -nostdlib -ffreestanding

SRCS = $(shell find src -name '*.[cS]')
OBJS = $(patsubst %, build/%.o, $(SRCS))

TOTAL_FILES := $(words $(OBJS))
COUNTER = 0
define progress
	$(eval COUNTER=$(shell echo $$(($(COUNTER)+1))))
	printf "[%d/%d] %s\n" $(COUNTER) $(TOTAL_FILES) $(1)
endef

.PHONY: default
default: build/kernel.elf

build/src/%.S.o: src/%.S
	@mkdir -p $(dir $@)
	@$(call progress, "Assembling $<")
	@$(CC) $(ASMFLAGS) -MMD -MF $@.d -c $< -o $@

build/src/%.c.o: src/%.c
	@mkdir -p $(dir $@)
	@$(call progress, "Compiling $<")
	@$(CC) $(CFLAGS) -MMD -MF $@.d -c $< -o $@

LDSCRIPT=src/linker.ld
build/kernel.elf: $(OBJS) | $(LDSCRIPT)
	@mkdir -p $(dir $@)
	@echo Linking $@
	@$(LD) $(LDFLAGS) -T $(LDSCRIPT) $^ -o $@

.PHONY: run
run: build/kernel.elf
	@mkdir -p shared
	@qemu-system-x86_64 \
		 -M microvm,pcie=off,acpi=off \
		 -m 64M \
		 -no-reboot \
		 -nographic \
		 -netdev user,id=net0 \
		 -device virtio-net-device,netdev=net0 \
		 -fsdev local,id=shared_folder,path=shared,security_model=mapped-xattr \
		 -device virtio-9p-device,fsdev=shared_folder,mount_tag=shared \
		 -device virtio-serial-device,id=virtio-serial0 \
		 -kernel $<

clean:
	@rm -rf build

-include $(OBJS:.o=.o.d)
