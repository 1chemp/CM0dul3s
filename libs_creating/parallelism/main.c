#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define MAXNITEMS 1024

/*
  Статистический анализ. Имеется несколько массивов данных (разного размера).
  Требуется определить математическое ожидание в каждом массиве.
  Обработка каждого массива выполняется в отдельном процессе.
*/

// инициализируем мьютекс
struct {
	pthread_mutex_t	mutex;
	int	buff[MAXNITEMS];
	int	nput;
	int	nval;
} shared = { 
	PTHREAD_MUTEX_INITIALIZER
};


int expectation(int* var, size_t size) {
	
	int sum = 0;
	size_t i;

	for (i = 0; i < size; i++) sum += var[i];

	return (sum/size);
}


void* processing(void* counter) {

	// получаем случайную размерность массива
	// и блокируем мьютекс
	pthread_mutex_lock(&shared.mutex);
	int n = rand() % 100; int i;
	
	int* array = (int*)malloc(sizeof(int)*n);

	// заполняем массив случайными числами
	for (i=0; i<n; i++) array[i] = rand() % 100;

	// рзблокируем мьютекс
	pthread_mutex_unlock(&shared.mutex);

	// выводим информацию о массиве + считаем мат. ожидание
	int id = pthread_self();
	printf("\nThread id (%d) create an array with lenght = %d was be created !\n", id, n);
	
	printf("Array: ");

	for (i=0; i<n; i++) printf("|%d", array[i]);
	printf("|\n");

	printf("Expected math value of this array: %d\n", expectation(array, n));

	pthread_exit((void*)array);
}

int main(int argc, char* argv[]) {
	int counter = 0, result;
	int param = atoi(argv[argc-1]);

	pthread_t threads[param];
	void* status[param];

	// запускаем потоки
	srand(time(0));

	for (int i=0; i < param; i++) {
		result = pthread_create(&threads[i], NULL, processing, &counter);

		if (result != 0) {
			perror("Creating the first thread");
			return EXIT_FAILURE;
		}	
	}

	// ожидаем выполнение потоков и по окончанию освобождаем память
	for (int j=0; j < param; j++) {
		result = pthread_join(threads[j], &status[j]);
		if (result != 0) {
			perror("Joining the first thread");
			return EXIT_FAILURE;
		}
		free(status[j]);
	}

	printf("\nDone!\n");
	return 0;
}

