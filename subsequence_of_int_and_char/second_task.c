#include <stdio.h>
#include <stdlib.h>
#define SIZE 512

struct Sequence {
	int current_index;
	char* sequence;
};

// вывод введенной послеовательности 
void writeIntoUser(struct Sequence data, int* len) {
	printf("\n+--- Number of sequence: #%d ---+\n", data.current_index);	
	int i,j,lock = 1,counter = 0;
	int* splicing = (int*)malloc(SIZE);
	// Сканируем последовательность на присутствие в ней разных типов данных,
	// т.е. ищем подпоследовательности
	printf("[*] Scanning on differents types !\n");
	for (i=0; data.sequence[i] != '\0'; i++) {
		if (i == (*len-3)) { splicing[counter] = i; counter++; break;}

		if (data.sequence[i] == '0') {
			printf("[+] Type <CHAR> of SEQUENCE was be decected in INDEX: %d!\n", i);
			// каждый нечетный индекс эл-та(1,3,5,..) - индекс на первый элемент ПОДпоследовательности
			splicing[counter] = i; counter++;
			// каждый четный индекс эл-та(0,2,4,..) - границы ПОДпоследовательности
			splicing[counter] = i+1; counter++;
			lock = 1;	
		}
		
		if (lock && ((int)data.sequence[i] >= 49 && (int)data.sequence[i] <= 57)) {
			printf("[+] Type <INT> of SEQUENCE was be decected in INDEX: %d!\n", i);
			splicing[counter] = i; counter++;
			splicing[counter] = i+1; counter++;
			lock = 0;
		}
	}
	splicing = (int*)realloc(splicing, counter);

	// Раскомментируйте, если нужно посмотреть на границы и первые элементы подпоследовательностей
	// printf("Splices: ");
	// for (j=0; splicing[j] != i;j++) {
	// 	printf("%d ", splicing[j]);
	// }
	// printf("%d\n", i);

	printf("[*] Printing clear sequence by subsequnses!\n"); lock = 1;
	// Печатаем "очищенную" последовательность.
	// Без граничных, например 0, N или 00
	printf("[=] Result: ");
	counter = 0;
	while (1) {
		if (!(counter%2)) {
			if (data.sequence[splicing[counter]]=='0'&& lock) {
				printf("| Type <CHAR>: ");
				lock = 0;
				counter++;
			} 
			else if (((int)data.sequence[splicing[counter]]>=49 && (int)data.sequence[splicing[counter]]<=57) && lock) {
				printf("| Type <INT>: ");
				lock = 0;
				counter++;
			}
		}
		if (counter % 2) {
			int left_s = splicing[counter];
			int right_s = splicing[counter+1]; 

			for (int kk=left_s; kk<right_s; kk++) {
				printf("%c", data.sequence[kk]);
			}

			if (right_s == i) {
				printf(" |");
				printf("\n+------------- #%d -------------+\n", data.current_index);
				break;
			}
			lock = 1; counter += 1;
		}
	}
	free(splicing);
}

// читаем и запоминаем последовательность в структуру (для удобства)
void readRememberSequence(char* src, int* seq_num) {
	// +--- Запоминаем данные ---+
	printf("[*] INT OR STR Sequence: ");
	int real_len, counter = 0, len = 0;
	
	fgets(src, SIZE, stdin);
	// изменяем границу с 512 байт до конца последовательности.
	for (;src[len] != '\0'; len++); src = (char*)realloc(src, len);
	real_len = len-1; // без '\0'

	struct Sequence data={*seq_num, src};
	// +--- Завершили запоминание, погружаем все в структуру ---+
	writeIntoUser(data, &real_len);
}

int main() {
	int number; printf("[*] Enter a number of sequences: "); scanf("%d", &number);
	getchar();
	char* seq = (char*)malloc(SIZE);

	for (int i=0; i<number; ++i)
		readRememberSequence(seq, &i);
	
	free(seq);
	return 0;
}