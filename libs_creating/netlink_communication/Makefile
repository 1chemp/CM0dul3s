obj-m += kernel_space_prog.o

all:
	gcc user_space_prog.c -o user_space_prog
	make -C /lib/modules/$(shell uname -r)/build  M=$(PWD) modules 
clean:
	rm user_space_prog
	make -C  /lib/modules/$(shell uname -r)/build  M=$(PWD) clean
