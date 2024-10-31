#ifndef _LIST_H //Метод условной компиляции, для предотвращения повторной компиляции кода
#define _LIST_H //Если макрос не был определен, код компилируется
//Заголовочный файл с объявлением прототипов функций, структур и станд. библиотек

#include <stdio.h> //Объявление стандартных библиотек
#include <stdlib.h>

typedef struct _node Node;

int getsize(Node** head);
Node* create_node(int data);
void list_push_front(Node** head, int data);
void list_push_back(Node** head, int data);
Node* list_pop_front(Node** head);
Node* list_pop_back(Node** head);
void list_push_index(Node** head, int data, int index);
Node* list_pop_index(Node** head, int index);
void print_list(Node** lst);
void funcdeleting(Node** head, int a, int b);
void free_list(Node** head);

#endif