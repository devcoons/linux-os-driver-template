SRCDIR=src/
BINDIR=bin/
CC=gcc
NAME=driver
C_FILES := $(wildcard $(SRCDIR)*.c)
obj-m := $(SRCDIR)$(NAME).o 
module-objs := $(C_FILES:.c=.o) 

KDIR  := /lib/modules/$(shell uname -r)/build
PWD   := $(shell pwd)

default:
	@mkdir -p $(BINDIR)
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	@mv *.* $(BINDIR)
	@mv $(SRCDIR)*.o $(BINDIR)
	@mv $(SRCDIR)*.ko $(BINDIR)
	@mv $(SRCDIR)*.mod.* $(BINDIR)
clean:
	rm -f $(SRCDIR)*.o
	rm -f $(SRCDIR)*.ko
	rm -f $(SRCDIR)*.mod.*
	rm -f $(BINDIR)*
	rm -r $(BINDIR)