#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

struct arguments {
    int sockfd;
    int newsockfd;
    char* line;
};


void* child_process(struct arguments* args) {
    int fd[2], result, n;

    result = fork();

    if (result < 0) {
        printf("Can't fork process");
        exit(1);
    }
    else if (result > 0) {
        // close(args->sockfd);

        while ( n = read(args->newsockfd, args->line, 999) > 0 ) {
        
            if ((n = write(args->newsockfd, args->line, strlen(args->line)+1)) < 0) {
                perror(NULL);
                close(args->sockfd);
                close(args->newsockfd);
                exit(1);
            }
        }
    }
}

void main() {

    int sockfd, newsockfd;
    int clilen;
    int child_res;
    char line[1000];
    struct sockaddr_in servaddr, cliaddr;
    pthread_t child_thid;


    /* Создаем TCP-сокет */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Error in main 55 "); perror(NULL);
        exit(1);
    }
    
    /* Заполняем структуру для адреса сервера: семейство
    протоколов TCP/IP, сетевой интерфейс – любой, номер 
    порта 51000. Поскольку в структуре содержится 
    дополнительное не нужное нам поле, которое должно 
    быть нулевым, побнуляем ее всю перед заполнением */

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family= AF_INET;
    servaddr.sin_port= htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    /* Настраиваем адрес сокета */
    if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        printf("Error in main 72"); perror(NULL);
        close(sockfd);
        exit(1);
    }
    
    /* Переводим созданный сокет в пассивное (слушающее) 
    состояние. Глубину очереди для установленных 
    соединений описываем значением 15 */
    
    if (listen(sockfd, 15) < 0){
        printf("Error in main 82"); perror(NULL);
        close(sockfd);
        exit(1);
    }
    struct arguments args;

    while (1) {
        clilen = sizeof(cliaddr);
        
        if((newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) < 0){
            printf("Error in main 92"); perror(NULL);
            close(sockfd);
            exit(1);
        }

        args.sockfd = sockfd; args.newsockfd = newsockfd; args.line = line;

        child_process(&args);

        close(newsockfd);
    }
}