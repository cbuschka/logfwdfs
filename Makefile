obj-m += logfwdfs.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

run:	all
	sudo insmod logfwdfs.ko && sudo rmmod logfwdfs.ko  && dmesg
