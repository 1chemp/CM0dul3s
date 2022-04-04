#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {
    int fd, result;
    size_t size;
    char resstring[14];

    //close(fd[0]);
    fd = atoi (argv[1]);
    /* Пробуем прочитать из pip'а 14 байт в массив, т.е. всю записанную строку */
    size = read(fd, resstring, 14);

    if(size < 0) {
        /* Если прочитать не смогли, сообщаем об ошибке и завершаем работу */
        printf("Can\'t read string\n");
        exit(-1);
    }

    /* Печатаем прочитанную строку */

    printf("%s",resstring);

    /* Закрываем входной поток и завершаем работу */

    close(fd);


    return 0;
}
