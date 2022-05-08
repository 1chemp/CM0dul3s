# SYS-PROG & LIBS_CREATING
<br>
+---- ./libs_creating/sysfsToKeyboard.c ----+
<br>
Description: This program makes kernel module in linux<br>
<br>
<img src="beautiful_image.jpg"></img><br>
Usage:<br>
$ sudo su<br>
# make<br>
# insmod sysfsToKeyboard.ko<br>
Now this module is active<br>
# dmesg | tail -5 // for show logs<br>
# cat /sys/kernel/systest/test (output would be 0)<br>
# echo 7 > /sys/kernel/systest/test<br>
As a result, you should watch the blinking LEDs on your keyboard!<br>
<br>
+--- Deleting module ---+<br>
# rmmod sysfsToKeyboard.ko<br>
# make clean<br>
<br>
<br>
+---- Enjoy ----+
