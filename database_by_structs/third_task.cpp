#include <stdio.h>
#include <malloc.h>
#define SIZE 128

// изменяет границу выделенной памяти, а также возвращает длину фамилии.
int validateSName(char* sname) {
    int len = 0;
    for (;sname[len] != '\0'; len++); sname = (char*)realloc(sname, len-3);
    return len;
}

// просто возвращает длину строки
int myLen(const char* str) { int len = 0; for (;str[len] != '\0'; len++); return len; }

struct Date {
    Date() {
        this->dd = 30;
        this->mm = 3;
        this->yyyy = 2022;
    }
    Date(int* yyyy, int* mm, int* dd) {
        this->yyyy = *yyyy; this->mm = *mm; this->dd = *dd;
    }

    void printDate(char* date_name) {
        printf("%s: %d-%d-%d\n", date_name, this->yyyy, this->mm, this->dd);
    }

    int dd,mm,yyyy;
};

struct Student {
    int num;
    const char* surname;
    Date date_of_receipt, date_of_expulsion;

    void printStudent() {
        if (this->num != -1) {
            printf("[*] Index of student: %d\n", this->num);
            printf("[*] Name of student: %s", this->surname);
            this->date_of_receipt.printDate("[*] Date of receipt");
            this->date_of_expulsion.printDate("[*] Date of expulsion");
        }
    }
};

struct Database {
    FILE* fp;
    Student* table = (Student*)malloc(SIZE);

    ~Database() {
        free(table);
    }

    // сохранение базы данных в файле
    void saveIntoTXT(int* len) {
        fp = fopen("db.txt", "w");
        fprintf(fp, "%s", "+---- Database of students ----+\n");

        for (int i=0; i<*len; i++) {
            if ( table[i].num != -1) {
                fprintf(fp, "\n[*] Index of student: %d\n", table[i].num);
                fprintf(fp, "[*] Name of student: %s", table[i].surname);
                fprintf(fp, "[*] Date of receipt: %d-%d-%d\n",    table[i].date_of_receipt.yyyy,
                                                                table[i].date_of_receipt.mm,
                                                                table[i].date_of_receipt.dd);
                fprintf(fp, "[*]Date of expulsion: %d-%d-%d\n\n",   table[i].date_of_expulsion.yyyy,
                                                                table[i].date_of_expulsion.mm,
                                                                table[i].date_of_expulsion.dd);
            }
        }
        fprintf(fp, "%s", "\n+---- FINISH OF DATABASE ----+");
        fclose(fp);

        printf("Data was be downloaded in file 'db.txt' successfully!\n");
    }
    // просмотр таблицы
    void watchTheTable(int* len) {
        printf("\n+---- Watching the Table of Students ----+\n");
        for (int j=0; j<*len; j++) {
            this->table[j].printStudent();
        }
        printf("\n+---- LIST OF STUDENTS FINISHED THERE ----+\n");
    }
    // сортировка таблицы по фамилии(имени) студентов
    void sortTable(int* len) {
        printf("\n+---- Sorting of table by surname was be started! ----+\n");

        for (int i=0;i<(*len-1); i++)
        {
            for (int j = (*len-1); j>i; j--)
            {
                if (table[j-1].surname[0] > table[j].surname[0]) {
                    Student temp = table[j - 1];
                    table[j - 1] = table[j];
                    table[j] = temp;
                }
            }
        }
        printf("\n+---- Sorting of table by surname FINISHED! ----+\n");
    }
    // поиск студента по его фамилии
    void searchTheStudent(int* len) {
        
        printf("\n+---- Process of searching student was be started! ----+\n");
        printf("Please, enter full surname or part of interested student: ");
        char* search_st = (char*)malloc(SIZE); fgets(search_st, SIZE, stdin);
        int search_st_len = validateSName(search_st);
        
        int coincidences = 0, foo; Student result;

        for (int k=0; k<*len; k++) {
            foo = 0;
            Student tmp = table[k];
            const char* checking = table[k].surname;
            int check_len = myLen(checking);

            for (int i=0, j=0; i<search_st_len,j<check_len; i++,j++) {
                if (i == search_st_len && j == check_len) 
                    break;
                else if (search_st[i] == checking[j]) {
                    foo++;
                }
                else { continue; }
            }
            if (foo > coincidences) { foo = coincidences; result = tmp; }
        }
        printf("Data about searched student :\n");
        result.printStudent();
        printf("\n+--- Process of searching student was finished successfully ! ----+\n");
    }

    // удаление студента по его фамилии
    void deleteStudent(int* len) {
        printf("\n+---- Deleting student ! ----+\n");
        printf("Please, enter the last name of student to be removed: ");
        char* search_st = (char*)malloc(SIZE); fgets(search_st, SIZE, stdin);
        (void*)validateSName(search_st);
        const char* del = "DELETED";

        for (int i=0; i<*len; i++) {
            if (table[i].surname[0] == search_st[0]) {
                table[i].surname = del;
                table[i].num = -1;
                table[i].date_of_receipt.yyyy = 0; table[i].date_of_receipt.mm = 0; table[i].date_of_receipt.dd = 0;
                table[i].date_of_expulsion.yyyy = 0; table[i].date_of_expulsion.mm = 0; table[i].date_of_expulsion.dd = 0;
            }
        }
        printf("\n+---- Process of deleting student finished successfully ! ----+\n");
    }

    // редактирование студента по его индексу
    void editStudent(int* len) {
        printf("\n+---- Proccess of editing student was be started ----+\n"); int ind;
        printf("Please, enter index of student to edit him: "); scanf("%d", &ind); getchar();
        ind -= 1;

        Student tmp;

        printf("[+] Enter the new surname: ");
        char* new_surname = (char*)malloc(SIZE); fgets(new_surname, SIZE, stdin);
        (void*)validateSName(new_surname); int yyyy, mm, dd;
        
        tmp.num = table[ind].num; tmp.surname = (const char*)new_surname;

        printf("\n[*] Enter new date of expulsion!\n");
        printf("[+] Year (YYYY): "); scanf("%d", &yyyy); getchar();
        printf("[+] Month (MM): "); scanf("%d", &mm); getchar();
        printf("[+] Day (DD): "); scanf("%d", &dd); getchar();

        Date expulsion(&yyyy, &mm, &dd);
        tmp.date_of_receipt = table[ind].date_of_receipt;
        tmp.date_of_expulsion = expulsion;

        table[ind] = tmp;
        printf("\n+---- Process of  editing student was be finished successfully ! ----+\n");
    }
};

int main(int argc, char* argv[]) {

    int number, i, yyyy, mm, dd;
    // получаем количество студентов, которые будут введены.
    printf("[*] Enter number of students to insert to DB: "); scanf("%d", &number); getchar();

    // Инициализируем Базу данных студентов.
    Database db;
    // изменяем границу по памяти под студентов.
    db.table = (Student*)realloc(db.table, number);

    // получаем фамилию студента, валидируем ее по границе, заполняем БД
    // *** ввод с клавиатуры данных о студентах ***
    for (i=0; i<number; i++) {
        char* sname = (char*)malloc(SIZE);        
        printf("\n[+] Surname of student %d: ", i+1); fgets(sname, SIZE, stdin);
        (void*)validateSName(sname);
        db.table[i].surname = (const char*)sname; db.table[i].num = (i+1);

        printf("\n[*] Entering data about date of RECEIPT.\n");
        printf("[+] Year (YYYY): "); scanf("%d", &yyyy); getchar();
        printf("[+] Month (MM): "); scanf("%d", &mm); getchar();
        printf("[+] Day (DD): "); scanf("%d", &dd); getchar();
        Date receipt(&yyyy, &mm, &dd);
        db.table[i].date_of_receipt = receipt;

        printf("\n[*] Entering data about date of EXPULSION.\n");
        printf("[+] Year (YYYY): "); scanf("%d", &yyyy); getchar();
        printf("[+] Month (MM): "); scanf("%d", &mm); getchar();
        printf("[+] Day (DD): "); scanf("%d", &dd); getchar();
        Date expulsion(&yyyy, &mm, &dd);
        db.table[i].date_of_expulsion = expulsion;

        printf("[!] This student was be inserted!\n", sname);
    }
    // clear buffer if it need
    // scanf("%*[^\n]");
    // scanf("%*c");

    bool flag = true;
    int choice;

    while (flag) {
        printf("\n++++ MAIN MENU ++++\n");
        printf("0 - Normal exit;\n");
        printf("1 - Sort table by last name of student;\n");
        printf("2 - Saving the table to a text document;\n");
        printf("3 - Table view;\n");
        printf("4 - Student search in the table;\n");
        printf("5 - Removing a student from a table;\n");
        printf("6 - Edit student data;\n");
        printf("Your choise: "); scanf("%d", &choice); getchar();

        switch (choice) {
            case 0: {
                flag = false;
                break;
            }
            case 1: {
                db.sortTable(&number);
                break;
            }
            case 2: {
                db.saveIntoTXT(&number);
                break;
            }
            case 3: {
                db.watchTheTable(&number);
                break;
            }
            case 4: {
                db.searchTheStudent(&number);
                break;
            }
            case 5: {
                db.deleteStudent(&number);
                break;
            }
            case 6: {
                db.editStudent(&number);
                break;
            }
            default: {
                printf("Not such choice there. Try again!");
                break;
            }
        }
    }

    // сортировка таблицы по фамилии
    // db.sortTable(&number);

    // сохранение в текстовый документ.
    // db.saveIntoTXT(&number);

    // просмотр таблицы
    // db.watchTheTable(&number);

    // поиск студента
    // db.searchTheStudent(&number);

    // удаление студента
    // db.deleteStudent(&number);

    // опционально вызвать после удаления
    // db.watchTheTable(&number);
    // db.saveIntoTXT(&number);

    // редактирование данных студента
    // db.editStudent(&number);

    // опционально вызвать после
    // db.watchTheTable(&number);
    return 0;
}