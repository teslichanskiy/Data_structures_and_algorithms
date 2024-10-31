//Курсовая работа. Задание КП8. Вариант [8,4,7]
//Выполнил студент группы М8О-104Б-22
//Тесля Данила Сергеевич

#include "kp8header.h"

int main(int argv, char* argc[]) {
    int value = 0, index = 0, a = 0, b = 0; //Переменные для ввода значения узлов, ввода индекса, ввода начала и конца дипазона соответственно
    Node* lst = NULL;
    int flag = 1;//Переменная для меню выбора
    enum var_cases {         //Для удобства в switch case
        ADDBEGIN = 1,
        ADDEND = 2,
        ADDINDEX = 3,
        DELETEBEGIN = 4,
        DELETEEND = 5,
        DELETEINDEX = 6,
        DELETEFUNCTION = 7,
        PRINT = 8
    };
    while (1) {
        printf("\nЧто Вы хотите сделать? \n [1] - Добавить узел в начало\n [2] - Добавить узел в конец\n [3] - Добавить узел по индексу\n\
 [4] - Удалить узел в начале\n [5] - Удалить узел в конце\n [6] - Удалить узел по индексу\n [7] - Удалить узлы в диапазоне значений\n\
 [8] - Напечатать список\n [0] - Завершить\n");
        fscanf(stdin, "%d", &flag);
        switch (flag) {
        case ADDBEGIN:  //Добавление нового узла в конец очереди
            printf("Введите значение узла:\n");
            fscanf(stdin, "%d", &value);
            list_push_front(&lst, value);
            break;

        case ADDEND: //Удаление узла из начала очереди
            printf("Введите значение узла:\n");
            fscanf(stdin, "%d", &value);
            list_push_back(&lst, value);
            break;

        case ADDINDEX: //Сортировка вставками
            printf("Введите значение узла:\n");
            fscanf(stdin, "%d", &value);
            printf("Введите индекс добавляемого элемента:\n");
            fscanf(stdin, "%d", &index);
            list_push_index(&lst, value, index);
            break;

        case DELETEBEGIN: //Сортировка вставками
            Node* some_node1 =list_pop_front(&lst);
            free(some_node1);
            break;

        case DELETEEND: //Сортировка вставками
            Node* some_node2 =list_pop_back(&lst);
            free(some_node2);
            break;

        case DELETEINDEX: //Сортировка вставками
            printf("Введите индекс удаляемого элемента:\n");
            fscanf(stdin, "%d", &index);
            Node* some_node3 = list_pop_index(&lst, index);
            free(some_node3);
            break;

        case DELETEFUNCTION: //Сортировка вставками
            printf("Введите диапазон:\n");
            printf("От: ");
            fscanf(stdin, "%d", &a);
            printf("До: ");
            fscanf(stdin, "%d", &b);
            funcdeleting(&lst, a, b);
            break;

        case PRINT: //Вывод очереди на экран
            print_list(&lst);
            printf("\nSize = %d\n", getsize(&lst));
            break;

        default:
            free_list(&lst);
            exit(0);
        }
    }

    return 0;
}
