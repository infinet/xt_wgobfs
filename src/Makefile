modname := xt_WGOBFS
obj-m := $(modname).o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := "$$(pwd)"

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
