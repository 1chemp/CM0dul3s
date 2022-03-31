#include <stdio.h>
#include <malloc.h>
#define SIZE 512

// функция возвращающая длину строки
int myLen(char* str) { int len = 0; for (;str[len] != '\0'; len++); return len; }

// выделяет память под двумерный массив и заполняет все пробелами
char** mtx() {
	char** matrix = (char*)malloc(SIZE);
	for (int i=0; i<SIZE; i++) {
		matrix[i] = (char*)malloc(SIZE);
		for (int j=0; j<SIZE; j++)
			matrix[i][j] = ' ';
		matrix[i][SIZE] = '\0';
	}
	return matrix;
}
// структура, представляющая собой треуровневый массив
struct Tripple {
	int num;
	char** mtxx;
};

int main() {
	FILE* file; char* estr;
	int num = 0, i, j; int len_of_stroke;
	char text[SIZE];
	char* valid_text = (char*)malloc(SIZE);
	char** matrix = mtx();
	
	// чтение
	file = fopen("text.txt", "r");
	while (1) {
		estr = fgets(text, sizeof(text), file);
		if (estr == NULL) {
			if (feof(file) != 0) {  
				printf ("\n[*] File text.txt was be readed completely\n");
				break;
			}
			else {
				printf ("\n[*] Unexpected Error !\n");
				break;
			}
		}
		// получаем длину и валидируем по ней границу выделенной памяти
		len_of_stroke = myLen(text);
		valid_text = (char*)realloc(valid_text, len_of_stroke);

		// копируем всю строку в одномерный динамический массив
		for (j=0; j<len_of_stroke; j++) valid_text[j] = text[j];
		valid_text[j] = '\0';

		// заполняем матрицу
		for (i=0; i<len_of_stroke; i++) matrix[num][i] = valid_text[i];
		num++;
	}
	fclose(file);

	struct Tripple* tripple = (struct Tripple*)malloc(SIZE);
	// Копируем из матрицы в трехмерный массив
	for (j=0; j<num; j++) {
		tripple[j].num = j;
		tripple[j].mtxx = mtx();

		for (int k=0; matrix[j][k] != '\0'; k++) {
			tripple[j].mtxx[j][k] = matrix[j][k]; 
		}
	}

	// Печатаем получившееся
	printf("+---- Printing array of structures of matrixes ----+\n");
	for(i=0; i<num; i++) {
		printf("Struct #%d\n", tripple[i].num+1);
		printf("Has data: ");
		for (j=0; tripple[i].mtxx[i][j] != '\0'; j++) {
			printf("%c", tripple[i].mtxx[i][j]);
		}
	}
	printf("\n+----    Printing was finished completely      ----+\n");

	// освобождаем выделенную память
	free(valid_text);
	free(matrix);
	free(tripple);
	return 0;
}