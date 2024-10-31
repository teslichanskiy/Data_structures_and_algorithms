#ifndef _TABLE_H
#define _TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define LEN_STR 100

typedef struct data {  //Структура для хранения одного блока (строки) исходных данных
    int key; //Поле со значением ключа
    char* text; //Поле со значением строки текста
} *Data;

Data init_data(); //Функция инициализации одной строки данных (ключ + строка)
int getsize(FILE* file1); //Функция получения количества ключей файла - "размер" данных
void read_data(Data* database, FILE* file1, FILE* file2); //Функция чтения данных из файлов и запись каждого блока в массив структур Data 
void sieve_heap(Data* database, int root, int leaf); //Функция построения правильной пирамиды - просеивание элементов
void heap_sort(Data* database, int size); //Функция пирамидальной сортировки на куче
bool is_sorted(Data* database, int size); //Проверка отсортированы ли данные для дальнейшего применения бинарного ыпоиска
bool is_revsorted(Data* database, int size); //Проверка отсортированы ли данные в обратном порядке для дальнейшего применения бинарного ыпоиска
void reverse_data(Data* database, int size); //Функция разворота данных    
int binary_search(Data* database, int size, int find_key); //Функция реализации бинарного поиска ключа
void rewrite_files (Data* database, FILE* file1, FILE* file2, int size); //Функция перезаписи файла
void print_data(Data* database, int size); //Функция вывода таблицы
void free_data(Data* database, int size); //Функция осовбождения памяти

#endif