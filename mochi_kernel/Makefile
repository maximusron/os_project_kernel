obj-m += mem_alloc_kernel.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod mem_alloc_kernel.ko
	sudo rmmod mem_alloc_kernel.ko
	dmesg

