#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define SIZE 2048

// stdin, stdout, stderr = 0, 1, 2

void createFile() {
      char *binaryPath = "/bin/bash";
      char *const args[] = {binaryPath, "-c" ,"cat shared1.c > test.txt", NULL};
      execve(binaryPath, args, NULL);
}

void bufferCreate(char* bffr) {
	
	char* estr;
	int fc[2];
	int result1; int res1 = pipe(fc);
	FILE* fp;
	char* text = (char*)malloc(100);

	if(res1 < 0){
    	printf("Can't create pipe\n");
    	exit(-1);
	}
	/* Порождаем новый процесс */
	result1 = fork();

	if (result1 < 0){
    	printf("Can\'t fork child\n");
   	 	exit(-1);
	} 
	else if (result1 > 0) {
		// в котором делаем создание файла и запись в него листинга.
    		close(fc[0]);
    		createFile();
    		close(fc[1]);
    		printf("Parent exit\n");
	} 
	else {
		close(fc[0]), close(fc[1]);
	}

	fp = fopen("test.txt", "r");
	// программно заливаем в буффер все имеющееся
	strcpy(bffr, "shared1.c :\n");

	if (fp == NULL) {printf("Unexpected error in opening file!"); exit(-1);}

	while (1) {
		estr = fgets(text, sizeof(text), fp);
		if (estr == NULL) {
			if (feof(fp) != 0) {  
				printf ("\n[*] File text.txt was be readed completely\n");
				break;
			}
			else{
				printf ("\n[*] Unexpected Error !\n");
				exit(-1);
			}
		}
		strcat(bffr, text);
	}
    fclose(fp);
	if (text) free(text);
}

int main() {

	// IPC descriptor
	int shmid;
	// Filename to generay IPC key
	char pathname[] = "shared1.c";
	// pointer to shared memory
	char* buffer = (char*)malloc(SIZE);
	// IPC key
	key_t key;

	if ((key = ftok(pathname,0)) < 0) {
		printf("Can't generate key!\n");
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
			printf("THERE!");
			if((shmid = shmget(key, SIZE*sizeof(char), 0)) < 0){
				printf("Can't find shared memory\n");
				exit(-1);
			}
		}
	}

	if((buffer = (char*)shmat(shmid, NULL, 0)) == (char*)(-1)){
		printf("Can't attach shared memory\n");
		exit(-1);
	}
	
	bufferCreate(buffer);
	// printf("%s", buffer);


	if (buffer) free(buffer);

	return 0;
}
