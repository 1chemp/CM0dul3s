#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int continuing_semaphore() {
    int semid; // обеспечивает доступ к семафоре по ключу

    char pathname[] = "to.c";

    key_t key; // обеспечивает подключение к уже существующему ключу или генерит новый

    struct sembuf mybuf;

    if((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        return 1;
    }

    if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t get semid\n");
        return 1;
    }

    mybuf.sem_op = 1;
    mybuf.sem_flg = 0;
    mybuf.sem_num = 0;

    if(semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
    }

    printf("Set condition\n");

    // удалим семафору
    if (semctl(semid, 0, IPC_RMID, 0) != 0) {
        return 1;
    }
    else {
        printf("Semaphore with id = %d was be DELETED completely!\n", semid);
    }

    return 0;
} 

int main()
{
    int *array; /* Указатель на разделяемую память */

    int shmid; /* IPC дескриптор для (подключения к) области разделяемой памяти */

    int new = 1; /* Флаг необходимости инициализации элементов массива */

    char pathname[] = "Makefile"; /* Имя файла, использующееся для генерации ключа */

    key_t key; /* IPC ключ для создания разделяемой памяти */

    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }

    /* Пытаемся эксклюзивно создать разделяемую память для сгенерированного ключа,
    т.е. если для этого ключа она уже существует системный вызов вернет отрицательное значение.
    Размер памяти определяем как размер массива из 3-х целых переменных,
    права доступа 0666 - чтение и запись разрешены для всех */

    if((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){

        if(errno != EEXIST){
            printf("Can\'t create shared memory\n");
            exit(-1);
        } 
        else {
            if((shmid = shmget(key, 3*sizeof(int), 0)) < 0) {
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
            new = 0;
        }
    }


    /* Пытаемся отобразить разделяемую память в адресное пространство текущего процесса. */
    if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    /* на этот момент времени первая программа должна была все просчитать, поэтому
    пусть теперь вторая программа выполнит свою часть */
    if (continuing_semaphore()) {
        printf("Error! Exiting..\n"); exit(-1);
    }
    else {
        printf("Ok! Continuing..\n");
    }

    if(new){
        array[0] = 0;
        array[1] = 1;
        array[2] = 1;
    } else {
        array[1] += 1;
        array[2] += 1;
    }


    /* Печатаем новые значения счетчиков, удаляем разделяемую память из адресного пространства текущего процесса и завершаем работу */ 

    printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n",
    array[0], array[1], array[2]);

    if(shmdt(array) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    else {
        if (shmctl(shmid, IPC_RMID, NULL) == 0) printf("Done!\n");
        else { printf("Error !"); exit(-1); }
    }

    return 0;
} 
