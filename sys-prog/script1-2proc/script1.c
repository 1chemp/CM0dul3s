#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// #define SIZE 100

int main(){

int fc[2]; int result1;
size_t size;
char resstring[3];

/* будем делать cat */

int res1 = pipe(fc);

if(res1 < 0){
    printf("Can\'t create pipe\n");
    exit(-1);
}
/* Порождаем новый процесс */
result1 = fork();

if(result1 < 0){
    printf("Can\'t fork child\n");
    exit(-1);
} 
else if (result1 > 0) {
    close(fc[0]);
    // ДАННЫЕ СЕЙЧАС запишутся в stdout
    // int local_res = execle("/bin/bash","/bin/bash", "-c", "cat hello.txt | grep -i \"me\"", NULL);
    // printf("%d", local_res);
    execl("/bin/cat", "-n", "hello.txt", NULL);
    // ЗАВЕРШАЕМ РОДИТЕЛЬСКУЮ ЗАПИСЬ
    close(fc[1]);
    printf("Parent exit\n");
} 
else {
    close(fc[1]);
    /* Пробуем прочитать из pip'а 2 байт в массив, т.е. всю записанную строку */
    size = read(fc[0], resstring, 2);
    if(size < 0){
    /* Если прочитать не смогли, сообщаем об ошибке и завершаем работу */
    printf("Can\'t read string\n");
    exit(-1);
    }
    resstring[3] = "\0";
    /* Печатаем прочитанную строку */
    printf("%s\n",resstring);
    /* Закрываем входной поток и завершаем работу */
    close(fc[0]);
}
return 0;
} 
