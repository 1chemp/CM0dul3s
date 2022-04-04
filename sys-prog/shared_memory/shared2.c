#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#define SIZE 2048

int main() {
	// IPC descriptor
	int shmid;
	// Filename to generate IPC key
	char pathname[] = "shared1.c";
	// pointer to shared memory
	char* buffer = (char*)malloc(SIZE);
	// IPC key
	key_t key;


	if ((key = ftok(pathname,0)) < 0) {
		printf("Can't generate key\n");
		exit(-1);
	}
	// create shared memory
	if((shmid = shmget(key, SIZE*sizeof(char), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
		
		// unexpected error
		if(errno != EEXIST) {
			printf("Can't create shared memory\n");
			exit(-1);
		} 
		else {
			// shared memory exists ?

			if((shmid = shmget(key, SIZE*sizeof(char), 0)) < 0){
				printf("Can't find shared memory\n");
				exit(-1);
			}
		}
	}

	if((buffer = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
		printf("Can't attach shared memory\n");
		exit(-1);
	}

    printf("Listing: %s\n", buffer);

	if(shmdt(buffer) != 0){
		printf("Can't detach shared memory\n");
		exit(-1);
	}
    else {
        if (shmctl(shmid, IPC_RMID, NULL) == 0) printf("Done!\n");
        else { printf("Error !"); exit(-1); }
    }
	return 0;
}
