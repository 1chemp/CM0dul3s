#SYS-PROG
<br>+--- ./sys-prog/shared\_semaphore\_memory/\*.c ---+<br>
<br>
<b>ru:</b> Есть две программы работающие с разделяемой памятью с использованием семафор Дейкстры<br>
Первая - инициализирует массив из трех целочисленных элементов,<br>
если он не был инициализирован ранее и заполняет его в соответствии с запуском (смотри код)<br>
Вторая - ждет пока первая программа завершится полностью,<br>
и выполняет свое заполнение массива и результат выводит на экран, также используя семафору,<br>
для того, чтобы синхронизировать выполнения двух программ.<br>
В конце выполнения вторая программа полностью подчищает мусор за собой (удаляет разделяемую память и семафору)<br>
<br>
<b>en:</b> There are two programs working with shared memory using Dijkstra's semaphore<br>
The first one initializes an array of three integer elements,<br>
if it has not been initialized before and fills it in according to the launch (see code)<br>
The second - waits until the first program is completed completely,<br>
and performs its filling of the array and displays the result on the screen, also using a semaphore,<br>
in order to synchronize the execution of two programs.<br>
At the end of the execution, the second program completely cleans up the garbage after itself (deletes the shared memory and the semaphore)<bt>
<br>
+---- Enjoy ----+