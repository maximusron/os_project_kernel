obj-m += mem_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test: 
	sudo dmesg -C
	sudo insmod mem_module.ko
	sudo rmmod mem_module.ko
	dmesg
