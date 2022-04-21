#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread(void *dummy) {
    pthread_t mythid;

    mythid = pthread_self();

    a = a+1;

    printf("Thread %d, Calculation result = %d\n", mythid, a);

    return NULL;
}

int main() {
    pthread_t first_thid, second_thid, main_thid;
    int first_result, second_result;

    // first pthread created and start
    first_result = pthread_create(&first_thid, (pthread_attr_t *)NULL, mythread, NULL);

    if(first_result != 0){
        printf ("Error on thread create, return value = %d\n", first_result);
        exit(-1);
    }
    printf("[FIRST] Thread created, thid = %d\n", first_thid);
    // first pthread was be finished !
    // delete first pthread ! (like semaphore)
    pthread_join(first_thid, (void **)NULL);

    // second pthread created and start (callback mythread)
    second_result = pthread_create(&second_thid, (pthread_attr_t *)NULL, mythread, NULL);

    if(second_result != 0){
        printf ("Error on thread create, return value = %d\n", second_result);
        exit(-1);
    }

    printf("[SECOND] Thread created, thid = %d\n", second_thid);
    // second pthread was be finished !
    // delete second pthread ! (like semaphore)
    pthread_join(second_thid, (void **)NULL);

    // main pthread started

    main_thid = pthread_self();

    a = a+1;

    printf("[MAIN] Thread %d, Calculation result = %d\n", main_thid, a);

    // main pthread finished !



    return 0;
} 
