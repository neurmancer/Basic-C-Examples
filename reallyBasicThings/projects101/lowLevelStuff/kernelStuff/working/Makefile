#If you rename the source file make sure you renmame it here too

obj-m += kernelActualDriverThingy.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean