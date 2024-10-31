//Курсовая работа. Задание №9. Вариант (9,2)
//Выполнил студент группы М8О-104Б-22
//Тесля Данила Сергеевич

#include "table.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Введите:\n%s ./filekeys ./filedata\n", argv[0]);
        return 1;
    }

    FILE *filekeys, *filedata;

    if ((filekeys = fopen(argv[1], "r+")) == NULL) { //Проверка, откроется ли файл на чтение
        printf("Не удалось открыть файл");
        exit(1);
    }

    if ((filedata = fopen(argv[2], "r+")) == NULL) { //Проверка, откроется ли файл на чтение
        printf("Не удалось открыть файл");
        exit(1);
    }

    int size = 0, flag = 0, key = 0, index = 0; //Размер, меню, значение искомого ключа, индекс искомого ключа соотв.
    enum {
        SORT = 1,
        SEARCH = 2,
        PRINT = 3,
        REWRITE = 4
    };
    size = getsize(filekeys);
    Data* database = calloc(size, sizeof(Data));
    read_data(database, filekeys, filedata);
    while (1) {
        printf("Что Вы хотите сделать?:\n [1] - Сортировать таблицу\n [2] - Поиск ключа в таблице \n\
 [3] - Вывод таблицы\n [4] - Перезаписать файл\n [0] - Завершить\n");
        fscanf(stdin, "%d", &flag);
        switch (flag) {
            case SORT:
                if (is_sorted(database, size)) {
                    printf("Таблица уже отсортирована\n");
                } else if (is_revsorted(database,size)) {
                    reverse_data(database,size);
                } else {
                    heap_sort(database, size);
                }
                break;

            case SEARCH:
                if (is_sorted(database, size)) {
                    printf("Введите ключ, который необходимо найти:\n");
                    fscanf(stdin, "%d", &key);
                    index = binary_search(database, size, key);
                    if (index != -1) {
                        printf("Соответствующее ключу поле таблицы: %s", database[index]->text);
                    } else {
                        printf("Такого ключа нет в таблице\n");
                    }
                } else if (is_revsorted(database, size)){
                    printf("Введите ключ, который необходимо найти:\n");
                    fscanf(stdin, "%d", &key);
                    reverse_data(database, size);
                    index = binary_search(database, size, key);
                    if (index != -1) {
                        printf("Соответствующее ключу поле таблицы: %s", database[index]->text);
                    } else {
                        printf("Такого ключа нет в таблице\n");
                    }
                    reverse_data(database, size);
                } else {
                    printf("Таблица неотсортирована!\n");
                }
                break;

            case PRINT:
                printf("Таблица:\n");
                print_data(database, size);
                break;

            case REWRITE:
                rewrite_files(database, filekeys, filedata, size);
                break;
            
            default:
                fclose(filekeys);
                fclose(filedata);
                free_data(database, size);
                return 0;
        }
    }  
}
