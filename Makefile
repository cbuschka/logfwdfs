obj-m += logfwdfs.o

CFLAGS_logfwdfs.o := -DDEBUG

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

insmod:	all
	sync && sudo insmod logfwdfs.ko

rmmod:
	sudo rmmod logfwdfs.ko

mount:
	mkdir -p $(PWD)/mnt && sudo mount -t logfwdfs none $(PWD)/mnt
