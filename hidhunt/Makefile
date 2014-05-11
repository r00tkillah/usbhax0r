obj-m := hidhunt.o
KDIR :=  /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	rm -rvf *.o *.ko *.mod.c *.symvers *.order .hidhunt* .tmp_versions
