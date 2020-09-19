obj-m += logfwdfs.o

CFLAGS_logfwdfs.o := -DDEBUG

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

run:	all
	sync && sudo insmod logfwdfs.ko && sudo rmmod logfwdfs.ko  && dmesg
