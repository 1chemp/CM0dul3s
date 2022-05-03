# LIBS FACTORY
<br>
+---- ./libs\_creating/main.c && Makefile ----+<br>
Usage: (in sudo mode)<br>
<br># make
<br># make clean (if it need)
<br># insmod main.ko
<br># echo "hello qwerty" > /proc/helloqwerty <br>
<p>Text in echo for example, dont worry, its works without errors in your HOST. </p>
<br>
<i>P.S.:you may be worried that only 10 bytes are allocated (kmalloc), but if you enter more it also works</i>
<br>
<br>
<br># cat /proc/helloqwerty (output will be "hello qwerty" in this case)
<br><br> IF U WANT TO DELETE MODULE "helloqwerty", follow the next instuctions:
<br># rmmod main.ko
<br><br>
+---- Enjoy ----+
<br>
<b>P.S.S.: My linux kernel version: 5.13.0</b>
