# LIBS_CREATING
<br>
+---- ./libs_creating/netlink_communication/kernel_space_prog.c && user_space_prog ----+<br>
Description: Netlink allows the user to use /sys/socket.h to communicate through the kernel rather than through protocols<br>
<img src="netlink.jpg"></img><br>
<br>
Usage:<br>
$ sudo su<br>
# make<br>
# insmod kernel_space_prog.ko<br>
# lsmod | grep kernel_space<br>
# ./user_space_prog<br>
+--- Deleting kernel module ---+<br>
# rmmod kernel_space_prog.ko<br>
# make clean<br>
<br>
+---- Enjoy ----+

