#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char **argv) {
    int sockfd; /* Дескриптор сокета */
    int n; /* Количество переданных или прочитанных 
              символов */
    int i; /* Счетчик цикла */
    char sendline[1000],recvline[1000]; /* Массивы для отсылаемой и принятой строки */
    struct sockaddr_in servaddr; /* Структура для адреса сервера */
    
    /* Сначала проверяем наличие второго аргумента в
    командной строке. При его отсутствии прекращаем 
    работу */
    
    if(argc != 2){
        printf("Usage: a.out <IP address>\n");
        exit(1);
    }

    /* Обнуляем символьные массивы */
    bzero(sendline,1000);
    bzero(recvline,1000);

    /* Создаем TCP сокет */
    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        perror(NULL); /* Печатаем сообщение об ошибке */
        exit(1);
    }

    /* Заполняем структуру для адреса сервера: семейство 
    протоколов TCP/IP, сетевой интерфейс – из аргумента 
    командной строки, номер порта 703. Поскольку в структуре
    содержится дополнительное не нужное нам поле, 
    которое должно быть нулевым, перед заполнением обнуляем 
    ее всю */
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(51000);
    
    if(inet_aton(argv[1], &servaddr.sin_addr) == 0){
        printf("Invalid IP address\n");
        close(sockfd);
        exit(1);
    }
    /* Устанавливаем логическое соединение через 
    созданный сокет с сокетом сервера, адрес которого мы занесли
    в структуру */
    if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    /* Три раза в цикле вводим строку с клавиатуры, отправляем 
    ее серверу и читаем полученный ответ */
    for(i=0; i<3; i++) {

        printf("String => ");
        fflush(stdin);

        fgets(sendline, 1000, stdin);
        
        if( (n = write(sockfd, sendline, strlen(sendline)+1)) < 0) {
            perror("Can\'t write\n");
            close(sockfd);
            exit(1);
        }

        if ((n = read(sockfd,recvline, 999)) < 0) {
            perror("Can\'t read\n");
            close(sockfd);
            exit(1);
        }

        printf("%s", recvline);
    }
    /* Завершаем соединение */
    close(sockfd);
}
