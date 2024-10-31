#include "26header.h"

int main(int argv, char *argc[]) {
    Queue queue = create_queue();
    int flag = 1;//Переменная для меню выбора
    int value = 0;
    enum var_cases {         //Для удобства в switch case
        ADD = 1,
        DELETE = 2,
        PRINT = 3,
        SORT = 4
    };
    while (1) {
        printf("\nЧто Вы хотите сделать? \n [1] - Добавить узел \n [2] - Удалить узел\n [3] - Показать очередь\n [4] - Запустить сортировку\n [0] - Завершить\n");
        fscanf(stdin, "%d", &flag);
        switch (flag) {        

            case ADD: //Добавление нового узла в конец очереди
                printf("Введите значение узла:\n");
                fscanf(stdin, "%d", &value);
                queue_push_back(queue, value);
            break;

            case DELETE: //Удаление узла из начала очереди
                Node delnode = queue_pop_front(queue);
                free(delnode);  
            break;      

            case PRINT:  //Вывод очереди на экран
                print_queue(queue);
                printf("\nSize = %d\n", getsize(queue));
            break;

            case SORT:  //Сортировка вставками
                Insertsort(queue);
            break;

            default:
                delete_queue(queue);
                exit(0);
        }
    }
    
    return 0;
}
