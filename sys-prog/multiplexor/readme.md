# SYS-PROG
<br>+--- ./sys-prog/multiplexor/\*.c ---+<br>
<br>
<b>ru:</b> Есть три программы.<br>
server.c - слушает сообщения от клиентов и посылает ответ о том, что сообщения были получены клиенту.<br>
client1.c client2.c - отсылают сообщения серверу в определенной последовательность (последовательности запуска)<br>
После они слушают ответ от сервера (ждут ответ). после прихода ответа, если длина сообщения не отрицательная, то завершают работу.<br>
Работают программы посредством очереди сообщений (для отсылки и принятия сообщения) и семафор (для ожидания сообщений от клиента или ожидания ответа от сервера). 
<br>
<b>en:</b> 
<br>
server.c - listens for messages from clients and sends a response that messages have been received to the client.<br>
client1.c client2.c - send messages to the server in a specific sequence (start sequences)<br>
After they listen to the response from the server (wait for a response). after the response arrives, if the message length is not negative, then the work is completed.<br>
Programs work through a message queue (for sending and receiving messages) and a semaphore (for waiting for messages from the client or waiting for a response from the server).
<br>
+---- Enjoy ----+
