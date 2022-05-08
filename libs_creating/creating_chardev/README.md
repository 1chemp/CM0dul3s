# LIBS_CREATING
<br>
+---- ./libs_creating/creating_chardev/chardev.c ----+<br>
<br>
<img src="image1.jpg"></img><br>
Usage:<br>
$ sudo su<br>
# make<br>
# insmod chardev.ko<br>
# lsmod | grep chardev<br>
# cat /dev/hello<br>
Output will be: I already told you %d times Hello world!<br>
were %d - number of starts this character device<br>
<br>
<br>
+---- Enjoy ----+
