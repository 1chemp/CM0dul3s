#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define LAST_MESSAGE 255 

int stop_semaphore(int param) {
    int semid; // обеспечивает доступ к семафоре по ключу

    char pathname[] = "client1.c";

    key_t key; // обеспечивает подключение к уже существующему ключу или генерит новый

    struct sembuf mybuf[2];

    if((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        return 1;
    }

    if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t get semid\n");
        return 1;
    }

    mybuf[param].sem_op = -2;
    mybuf[param].sem_flg = 0;
    mybuf[param].sem_num = 0;

    if (semop(semid, mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        return 1;
    }

    if (semctl(semid, 0, IPC_RMID, 0) != 0) {
        return 1; /* произошла какая то ошибка по удалению здесь */
    }
    else {
        printf("Semaphore with id = %d was be DELETED completely!\n", semid);
    }

    printf("Condition is unset\n");
    return 0;
}


void send_answer() {
    int msqid_answer;

    char pathname[] = "client2.c";

    key_t key;

    int len;

    struct mybuf_answer {
        long mtype;
        char mtext[81];
        int process_id;
    } my_answer_buf;

    if((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if((msqid_answer = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    }
    // отсылаем 2 раза для каждого из потоков
    for (int i = 1; i < 3; i++) {

        my_answer_buf.mtype = 1;
        my_answer_buf.process_id = 5;
        
        strcpy(my_answer_buf.mtext, "This is ANSWER for client");
        len = strlen(my_answer_buf.mtext)+1;

        if (msgsnd(msqid_answer, (struct msgbuf *) &my_answer_buf, len, 0) < 0) {
            printf("Can\'t send message to queue\n");
            msgctl(msqid_answer, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }
}


int main() {
    int msqid;

    char pathname[] = "Makefile";

    key_t key;

    int len, maxlen; /* Cчетчик цикла и длина информативной части сообщения */

    /* Ниже следует пользовательская структура для сообщения */

    struct mymsgbuf
    {
        long mtype;
        char mtext[81];
        int id;

    } mybuf;


    if((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    /* recieve */
    while(1) {

        maxlen = 81;

        if ( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0) < 0) {
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }

        if (mybuf.mtype == LAST_MESSAGE) {
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            break;
        }

        printf("message type = %ld, info = %s\n", mybuf.mtype, mybuf.mtext);
    }
    int res = stop_semaphore(0);

    if (res != 0) { printf("Some error for semaphore create\n"); }
    else { printf("Ok!\n"); }

    send_answer();

    int res2 = stop_semaphore(1);

    return 0;
} 