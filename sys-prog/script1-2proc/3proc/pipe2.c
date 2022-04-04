#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv){
    int fd, result;
    size_t size;
    char resstring[14];

    //close(fd[0]);
    fd = atoi (argv[1]);
    /* Пробуем записать в pipe 14 байт, т.е. всю строку "Hello, world!"
    вместе с признаком конца строки */

    size = write(fd, "Hello, world!\0", 14);

    if(size != 14){
        /* Если записалось меньшее количество байт, сообщаем об ошибке и завершаем работу */
        printf("Can\'t write all string\n");
        exit(-1);
    }
    return 0;
}
