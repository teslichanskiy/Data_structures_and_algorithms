#include "table.h"

Data init_data() { //Функция инициализации одной строки данных (ключ + строка)
    Data one_line = (Data)malloc(sizeof(*one_line));
    one_line->text = calloc(LEN_STR, sizeof(char));
    one_line->key = 0;
    return one_line;
}

int getsize(FILE* file1) { //Функция получения количества ключей файла - "размер" данных
    int size = 0, key = 0; 
    while (!feof(file1)) { //Пока не будет встречен символ EOF
        fscanf(file1, "%d", &key); //Считывается, но не сохраняется - просто идем по строкам и считаем
        size++;
    }

    rewind(file1); //Возврат указателя в файле к началу - на случай если будут еще операции с файлов
    return size;
}

void read_data(Data* database, FILE* file1, FILE* file2) { //Функция чтения данных из файлов и запись каждого блока в массив структур Data 
    int index = 0;
    while (!feof(file1) && !feof(file2)) { //Пока не встречен конец одного из файлов
        char temp_buffer[LEN_STR]; //Временный буфер для строки данных
        temp_buffer[LEN_STR - 1] = '\0';
        int keys = 0; //Временная переменная для ключей
        Data data = init_data(); //Инициализация одной строки данных (ключ + строка)
        fscanf(file1, "%d", &keys); //Чтение ключей из файла с ключами построчно
        data->key = keys;  //Заполнение поля ключей
        fgets(temp_buffer, LEN_STR, file2);  //Чтение текстовых строк из файла построчно
        strncpy(data->text, temp_buffer, LEN_STR); //Копирование в поле структуры
        if (data->text[0] == '\0') { //Если вдруг в конце файла с текстовыми данными стоит пустая строка
            break;
        }

        database[index] = data; //Добавление одной строки с данными в структуру
        index++;
    }

    rewind(file1);
    rewind(file2);
}

void sieve_heap(Data* database, int root, int leaf) { //Функция построения правильной пирамиды - просеивание элементов
    int max = 0, temp_key = 0; //max - индекс максимального потомка, остальные - временные переменные для обмена значениями
    char temp_buffer[LEN_STR];
    temp_buffer[LEN_STR - 1] = '\0';
    while (root * 2 <= leaf) { 
        if (root * 2 == leaf) { //Если это последний ряд, то максимальный потомок - левый
            max = root * 2;
        } else if (database[root * 2]->key > database[root * 2 + 1]->key) { //Если левый больше правого, то максимальный - левый
            max = root * 2;
        } else {   //Если правый больше левого, то максимальный - правый
            max = root * 2 + 1;
        }

        if (database[root]->key < database[max]->key) { //Если значение корня меньше значения максимального потомка
            temp_key = database[root]->key;  //Обмен значениями через временные переменные - перестраивание пирамиды
            database[root]->key = database[max]->key;
            database[max]->key = temp_key;
            strncpy(temp_buffer, database[root]->text, LEN_STR);
            strncpy(database[root]->text, database[max]->text, LEN_STR);
            strncpy(database[max]->text, temp_buffer, LEN_STR);
            root = max;
        } else { 
            break; //Если нет, значит максимальный элемент стал корнем, пирамида сформирована
        }
    }
}

void heap_sort(Data* database, int size) { //Функция пирамидальной сортировки на куче
    int temp_key = 0; //Временные переменные
    char temp_buffer[LEN_STR];
    temp_buffer[LEN_STR - 1] = '\0'; 
    for (int i = (size / 2) - 1; i >= 0; i--) { //Вызов функции просеивания, формирование нижнего ряда пирамиды
        sieve_heap(database, i, size - 1);
    }

    for (int i = size - 1; i >= 1; i--) { 
        temp_key = database[0]->key;  //Обмен значениями через временные переменные - перестраивание пирамиды
        database[0]->key = database[i]->key;
        database[i]->key = temp_key;
        strncpy(temp_buffer, database[0]->text, LEN_STR);
        strncpy(database[0]->text, database[i]->text, LEN_STR);
        strncpy(database[i]->text, temp_buffer, LEN_STR);
        sieve_heap(database, 0, i - 1); //Вызов функции просеивания 
    }
}

bool is_sorted(Data* database, int size) { //Проверка отсортированы ли данные для дальнейшего применения бинарного ыпоиска
    int flag = 0;
    for (int i = 1; i < size; i++) {
        if (database[i - 1]->key >= database[i]->key) {
            flag = 1;
            break;
        }
    }

    if (flag == 0) return true;
    else return false;
}

bool is_revsorted(Data* database, int size) { //Проверка отсортированы ли данные в обратном порядке для дальнейшего применения бинарного ыпоиска
    int flag = 0;
    for (int i = 1; i < size; i++) {
        if (database[i - 1]->key <= database[i]->key) {
            flag = 1;
            break;
        }
    }

    if (flag == 0) return true;
    else return false;
}

void reverse_data(Data* database, int size) { //Функция разворота данных
    char temp_buffer[LEN_STR];
    temp_buffer[LEN_STR - 1] = '\0';
    int temp_key = 0;
    for (int i = 0; i < size/2; i++) {
        temp_key = database[i]->key;  //Обмен значениями через временные переменные 
        database[i]->key = database[size - i - 1]->key;
        database[size - i - 1]->key = temp_key;
        strncpy(temp_buffer, database[i]->text, LEN_STR);
        strncpy(database[i]->text, database[size - i - 1]->text, LEN_STR);
        strncpy(database[size - i - 1]->text, temp_buffer, LEN_STR);
    }
}


int binary_search(Data* database, int size, int find_key) { //Функция реализации бинарного поиска ключа
    int middle = 0, left = 0, right = size - 1, index = 0; //Переменные хранят индексы получаемых в алгоритме - серединных элементов, левой и правой границ и найденного ключа соответсвтенно
    while (left <= right) { //Пока левая граница не зашла за правую
        middle = (right + left) / 2;  //Индекс серединного элемента в каждой итерации
        if (find_key > database[middle]->key) {//Если искомый ключ больше, то сдвигается левая граница
            left = middle + 1;
        }

        if (find_key < database[middle]->key) {//Если искомый ключ больше, то сдвигается правая граница
            right = middle - 1;
        }

        if (find_key == database[middle]->key) { //Если элемент найден, то функция вернет его индекс и поиск завершен
            index = middle;
            return index;
        }
    }

    return -1;  //Если не произошел выход из функции до этого, значит элемент не был найден
}

void rewrite_files (Data* database, FILE* file1, FILE* file2, int size) { //Функция перезаписи файла
    char temp_buffer[LEN_STR];
    temp_buffer[LEN_STR - 1] = '\0';
    int temp_key = 0;
    for (int i = 0; i < size; i++) {
        temp_key = database[i]->key;
        if (i != size - 1) fprintf(file1, "%d\n", temp_key);
        else fprintf(file1, "%d", temp_key);

        strncpy(temp_buffer, database[i]->text, LEN_STR);
        fputs(temp_buffer, file2);
    }
    rewind(file1);
    rewind(file2);
}

void print_data(Data* database, int size) { //Функция вывода таблицы
    printf("|========================================================|\n");
    printf("| Ключ |                  Строка                         |\n");
    printf("|========================================================|\n");
    for (int i = 0; i < size; i++) {
        printf("| %-4d | %-25s", database[i]->key, database[i]->text);
    }

    printf("|========================================================|\n");
}

void free_data(Data* database, int size) { //Функция осовбождения памяти
    for (int i = 0; i < size; i++) {
        free(database[i]->text);
        free(database[i]);
    }

    free(database);
}