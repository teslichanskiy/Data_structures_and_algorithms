#include "kp8header.h"

typedef struct _node { //Структура узла списка
    int value;  //Поле значения узла
    struct _node* prev_node; //Указатель на предыдущий узел 
    struct _node* next_node; //УКазатель на следующий ущел
} Node;

int getsize(Node** head) { //Функия получения размера списка
    int size = 0;   //Хранит значение длины списка
    if (*head == NULL) { //Если список пуст
        return size;
    }

    if (*head == (*head)->next_node) {
        size++;
        return size;
    }

    Node* this_node = (*head)->next_node;
    while (this_node != *head) {
        size++;
        this_node = this_node->next_node;
    }

    size++;
    return size;
}

Node* create_node(int data) {  //Инициализация структуры узла
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = data;
    newNode->prev_node = NULL;
    newNode->next_node = NULL;
    return newNode;
}

void list_push_front(Node** head, int data) { //Функция добавления в начало
    Node* newNode = create_node(data);
    if (*head == NULL) { //Если список пуст
        *head = newNode;
        (*head)->prev_node = *head; //Так как список циклический, то первый добавленный элемент содержит указатели на себя 
        (*head)->next_node = *head;
    } else {
        Node* lastNode = (*head)->prev_node;
        newNode->prev_node = lastNode;
        newNode->next_node = *head;
        (*head)->prev_node = newNode;
        lastNode->next_node = newNode;
        *head = newNode;
    }
}

void list_push_back(Node** head, int data) { //Функция добавления в конец
    Node* newNode = create_node(data);
    if (*head == NULL) {
        *head = newNode;
        (*head)->prev_node = *head;
        (*head)->next_node = *head;
    } else {
        Node* tempnode = (*head)->prev_node;
        newNode->prev_node = tempnode;
        newNode->next_node = *head;
        (*head)->prev_node = newNode;
        tempnode->next_node = newNode;
    }
}


Node* list_pop_front(Node** head) { //Функция удаления первого элемента
    if (*head == NULL) {
        printf("Список пуст\n");
        return NULL;
    } else {
        Node* this_node = *head;
        Node* temp_node = (*head)->prev_node;
        *head = (*head)->next_node;
        (*head)->prev_node = temp_node;
        temp_node->next_node = *head;
        printf("Удален узел: %d\n", this_node->value);
        return this_node;
    }
}

Node* list_pop_back(Node** head) { //Функция удаления последнего элемента
    if (*head == NULL) {
        printf("Список пуст\n");
        return NULL;
    } else {
        Node* this_node = (*head)->prev_node;
        Node* temp_node = (*head)->prev_node->prev_node;
        (*head)->prev_node = temp_node;
        temp_node->next_node = *head;
        printf("Удален узел: %d\n", this_node->value);
        return this_node;
    }
}

void list_push_index(Node** head, int data, int index) { //Функция добавления по индексу, получает индекс НА МЕСТО КОТОРОГО нужно добавить узел
    if (index > getsize(head)) {
        printf("Элемента с таким индексом не существует!\n");
        return;
    }

    if (index == 0) {
        list_push_front(head, data);
    } else {
        Node* temp_node = *head;
        for (int i = 0; i < index; i++) {
            temp_node = temp_node->next_node;
        }

        list_push_back(&temp_node, data);
    }
}

Node* list_pop_index(Node** head, int index) { //Функция удаления по индексу
    if (index > getsize(head) - 1) {
        printf("Элемента с таким индексом не существует!\n");
        return NULL;
    }

    if (*head == NULL) {
        printf("Список пуст\n");
        return NULL;
    } else {
        if (index == 0) {
            Node* some_node1 = list_pop_front(head); //Если удаляется первый по индексу элемент
            return some_node1;
        } else {
            Node* temp_node = *head;
            for (int i = 0; i <= index; i++) {
                temp_node = temp_node->next_node;
            }

            Node* some_node2 = list_pop_back(&temp_node); //Если удаляется любой другой элемент
            return some_node2;
        }
    }
}

void print_list(Node** head) { //Функция печати списка
    if (*head == NULL) {
        printf("Список пуст!\n");
        return;
    }

    printf("Список:\n");
    Node* this_node = *head;
    if (getsize(head) == 1) {
        printf("\n... (%d) ...", this_node->value);
        return;
    }

    printf("\n... (%d), ", this_node->value);
    this_node = this_node->next_node;
    while (this_node != (*head)->prev_node) {
        printf("(%d), ", this_node->value);
        this_node = this_node->next_node;
    }

    printf("(%d) ...\n", this_node->value);
}

void funcdeleting(Node** head, int a, int b) { //Функция удаление узлов в диапазоне значений
    if (*head == NULL) {
        printf("Список пуст!\n");
        return;
    } 

    int index = getsize(head);
    Node* temp_node = *head;
    for(int i = 0; i < index; i++){ //Прохождение по списку и поиск элементов удовлетворяющих условию
        if(temp_node->value >= a && temp_node->value <= b){
            Node* some_node = list_pop_index(head, i);
            free(some_node);
            i--;
            index--; //Уменьшение, так как удалили узел
        }

        temp_node = temp_node->next_node; 
    }
}

void free_list(Node** head) { //Функция освобождения памяти
    if (*head == NULL) {
        return;
    }
    Node* this_node = *head;
    Node* temp_node = this_node->next_node;
    do {
        temp_node = this_node->next_node;
        free(this_node);
        this_node = temp_node;
    } while (this_node != *head);
    *head = NULL;
}
