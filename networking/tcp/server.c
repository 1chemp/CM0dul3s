#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

void main() {

    int sockfd, newsockfd; /* Дескрипторы для 
                            слушающего и присоединенного сокетов */
    int clilen; /* Длина адреса клиента */
    int n;      /* Количество принятых символов */
    char line[1000];    /* Буфер для приема информации */
    struct sockaddr_in servaddr, cliaddr; /* Структуры 
                                            для размещения полных адресов сервера и 
                                            клиента */
    
    /* Создаем TCP-сокет */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror(NULL);
        exit(1);
    }
    
    /* Заполняем структуру для адреса сервера: семейство
    протоколов TCP/IP, сетевой интерфейс – любой, номер 
    порта 703. Поскольку в структуре содержится 
    дополнительное не нужное нам поле, которое должно 
    быть нулевым, побнуляем ее всю перед заполнением */

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family= AF_INET;
    servaddr.sin_port= htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    /* Настраиваем адрес сокета */
    if(bind(sockfd, (struct sockaddr *) &servaddr, 
    sizeof(servaddr)) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    
    /* Переводим созданный сокет в пассивное (слушающее) 
    состояние. Глубину очереди для установленных 
    соединений описываем значением 5 */
    
    if(listen(sockfd, 5) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    
    /* Основной цикл сервера */
    while(1) {
        /* В переменную clilen заносим максимальную
        длину ожидаемого адреса клиента */
        clilen = sizeof(cliaddr);
        /* Ожидаем полностью установленного соединения
        на слушающем сокете. При нормальном завершении 
        у нас в структуре cliaddr будет лежать полный 
        адрес клиента, установившего соединение, а в 
        переменной clilen – его фактическая длина. Вызов
        же вернет дескриптор присоединенного сокета, через
        который будет происходить общение с клиентом. 
        Заметим, что информация о клиенте у нас в
        дальнейшем никак не используется, поэтому 
        вместо второго и третьего параметров можно 
        было поставить значения NULL. */
        
        if((newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) < 0){
            perror(NULL);
            close(sockfd);
            exit(1);
        }

        /* В цикле принимаем информацию от клиента до
        тех пор, пока не произойдет ошибки (вызов read()
        вернет отрицательное значение) или клиент не
        закроет соединение (вызов read() вернет 
        значение 0). Максимальную длину одной порции 
        данных от клиента ограничим 999 символами. В
        операциях чтения и записи пользуемся дескриптором
        присоединенного сокета, т. е. значением, которое
        вернул вызов accept().*/
        
        while ((n = read(newsockfd, line, 999)) > 0) {
            /* Принятые данные отправляем обратно */
		printf("%s", line);
	    if ((n = write(newsockfd, line, strlen(line)+1)) < 0) {
                perror(NULL);
                close(sockfd);
                close(newsockfd);
                exit(1);
            }
        }
        /* Если при чтении возникла ошибка – завершаем работу */
        if (n < 0) {
            perror(NULL);
            close(sockfd);
            close(newsockfd);
            exit(1);
        }
        /* Закрываем дескриптор присоединенного сокета и
        уходим ожидать нового соединения */
        close(newsockfd);
    }
}
