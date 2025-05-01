# Define object files to build
obj-m += deadlock.o

# Define variables for cross-compilation
ARCH := arm
CROSS_COMPILE := /home/ahmed/x-tools/arm-training-linux-musleabihf/bin/arm-training-linux-musleabihf-

# Path to your kernel sources from the lab
KERNEL_DIR := /home/ahmed/embedded-linux-qemu-labs/kernel/linux

# Explicitly set the current directory
PWD := $(shell pwd)

# Default target: build modules
all:
	make -C $(KERNEL_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

# Clean target: clean up build files
clean:
	make -C $(KERNEL_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean
