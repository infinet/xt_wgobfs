MODULES_DIR := /lib/modules/$(shell uname -r)
KERNEL_DIR := ${MODULES_DIR}/build

# minimal gcc version for -Wimplicit-fallthrough=3 is 7.5
IS_GCC_ABOVE_MIN_VERSION := $(shell gcc -dumpversion | awk 'BEGIN {FS="."} {if (10*$$1+$$2>=75) {print 1} else {print 0}}')

ifeq "$(IS_GCC_ABOVE_MIN_VERSION)" "1"
	EXTRA_CFLAGS := -I$(src)/../include -DbKERNELMOD -Wimplicit-fallthrough=3
else
	EXTRA_CFLAGS := -I$(src)/../include -DbKERNELMOD
endif


obj-m += xt_WGOBFS.o
xt_WGOBFS-objs += xt_WGOBFS_main.o chacha8.o

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	make -C ${KERNEL_DIR} M=$$PWD $@;
install:
	cp xt_WGOBFS.ko $(MODULES_DIR)/kernel/net/netfilter/
	depmod -a
	modprobe xt_WGOBFS
	echo "xt_WGOBFS" > /etc/modules-load.d/wgobfs.conf

