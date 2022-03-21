#include <stdio.h>
#include <stdlib.h>
#define SIZE 1024
#define MAXCOL 64

// Вариант №9
// "Перевернуть" в строке все слова. Удалить слова – палинандромы.

void printMatrix(char** matrix, short* cols) {
	for (short j=0; j<*cols; j++) {
		printf("Row[0][%d] = \n",j);
		puts(matrix[j]);
	}
}

// создаем матрицу слов и ПРЕДВАРИТЕЛЬНО заполняем все пробелами.
// если было введено 3 слова через пробел, то получится 3x63 (доступно), каждый 64 эл-т нуль-терминатор
char** makeMatrix(const short* words_count) {
	size_t size = *words_count;
	char** matrix = (char*)malloc(MAXCOL);
	for (short i=0; i<size; i++) {
		matrix[i] = (char*)malloc(MAXCOL);
		for (short j=0; j<MAXCOL; j++)
			matrix[i][j] = ' ';
		matrix[i][size] = '\0';
	}
	return matrix;
}

void isPalindrom(char* word, short* len) {
	if (word[0] == word[*len-1]) {word[*len-1]=' ';}
}

// Суть - делаем обрезку начальной строки с помощью индексов пробелов в изначальной строку,
// также добавляем нуль-терминатор
char** algorithmSplicesInsert(char* all_str, short* all_len, short* spaces_ind, short* words_count) {

	char** row = makeMatrix(words_count);
	// printMatrix(row, words_count);
	short ind = 0, oldInd = 0; short i,j,k, counter, neg;

	for (i=0; i<*words_count; i++) {
		ind = spaces_ind[i]; counter = 0;

		for (j=oldInd; j<ind; j++) {
			row[i][counter] = all_str[j];
			counter++;
		}
		row[i][ind] = '\0';
		oldInd = ind+1;

		isPalindrom(row[i], &counter);

		char* spam = (char*)malloc(counter); neg = 1;
		for (short t=0; t != counter; t++) {
			spam[t] = row[i][counter-neg]; neg++;
		}
		spam[counter] = '\0';
		row[i] = spam;
	}
	return row;
}

int main() {
	// выделяем память под строку
	char* c = (char*)malloc(SIZE);
	printf("%s", "Hello, enter some string: "); fgets(c,SIZE,stdin);
	// printf("Was Entered: "); puts(c);
	
	short i, words_num = 0, ind = 0;

	short* space_indexes = (short*)malloc(SIZE);

	for (i=0;c[i]!=0;i++) if (c[i] == ' ' || c[i] == '\n') {words_num++; space_indexes[ind]=i; ind++;}

    printf("Lenght of text: %i\n",i-1);
	printf("Number of words: %i\n",words_num);

	// перевыделяем память ровно под строку и массив индексов (используя длины)
	c = (char *)realloc(c,i); space_indexes = (short*)realloc(space_indexes,ind);

	char** matrix = algorithmSplicesInsert(c, &i, space_indexes, &words_num);
	printf("Result string: ");
	
	for (short j=0; j<words_num; j++) {
		if (matrix[j][0] == ' ') continue;
		printf("%s ", matrix[j]);
	}
	printf("\n");

	free(c); free(space_indexes); free(matrix);
	return 0;
}