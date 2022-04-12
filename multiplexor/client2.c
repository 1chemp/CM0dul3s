#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define LAST_MESSAGE 255

int continue_semaphore_client2(int param) {

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

    mybuf[param].sem_op = 1;
    mybuf[param].sem_flg = 0;
    mybuf[param].sem_num = 0;

    if (semop(semid, mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        return 1;
    }

    printf("Condition is set\n");
    return 0;
}

void get_answer_client2() {

    int msqid_answer;

    char pathname[] = "client2.c";

    key_t key;

    int maxlen, len;

    struct mybuf_answer {
        long mtype;
        char mtext[81];
        int process_id;
        
    } my_answer_buf;

    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((msqid_answer = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    while(1) {

        maxlen = 81;
        /* recieve */
        if ( len = msgrcv(msqid_answer, (struct msgbuf *) &my_answer_buf, maxlen, 0, 0) < 0) {
            printf("Hello! Can\'t receive message from queue\n");
            exit(-1);
        }

        printf("message type = %ld, info = %s\n", my_answer_buf.mtype, my_answer_buf.mtext);

        break;
    }
}


int main() {

    int msqid;

    char pathname[] = "Makefile";

    key_t key;

    int i,len; /* Cчетчик цикла и длина информативной части сообщения */

    /* Ниже следует пользовательская структура для сообщения */

    struct mymsgbuf
    {
        long mtype;
        char mtext[81];
        int id_client2;

    } mybuf;


    if((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    for (i = 1; i <= 5; i++) {

        mybuf.mtype = 1;
        mybuf.id_client2 = 6;
        strcpy(mybuf.mtext, "This is text MESSAGE from client2");
        len = strlen(mybuf.mtext)+1;

        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }

    /* Отсылаем сообщение, которое заставит получающий процесс прекратить работу, с типом LAST_MESSAGE и длиной 0 */
    mybuf.mtype = LAST_MESSAGE;
    len = 0;

    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    int res = continue_semaphore_client2(0);

    if (res != 0) { printf("Some error for semaphore create\n"); }
    else { printf("Ok!\n"); }

    // receive answer 
    get_answer_client2();

    int res2 = continue_semaphore_client2(1);

    return 0;
} 