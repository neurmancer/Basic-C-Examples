# ================================================
# RICKROLL KERNEL MODULE MAKEFILE 
# ================================================

obj-m += rickroll.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules_install

uninstall:
	sudo rm -f /lib/modules/$(shell uname -r)/extra/rickroll.ko
	sudo depmod -a

.PHONY: all clean install uninstall