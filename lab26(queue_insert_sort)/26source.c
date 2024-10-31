#include "26header.h"

typedef struct _node { // Структура узла очереди
    int value;
    struct _node* next_node;
} *Node;

typedef struct _queue { // Структура очереди (размер, нач. и конеч. узлы)
    Node front; // Первый элемент
    Node last; // Последний элемент
} *Queue;

Queue create_queue() { // Создание пустой очереди
    Queue queue = (Queue)malloc(sizeof(*queue)); // Резервируем память
    queue->front = NULL;
    queue->last = NULL;
    return queue;
}

int getsize(Queue queue) {
    int size = 0;
    if (queue->front == NULL) {
        return size;
    }

    size++;
    Node this_node = queue->front;
    while (this_node->next_node) {
        size++;
        this_node = this_node->next_node;
    }

    return size;
}

bool isempty(Queue queue) {
    if(queue->front == NULL) return true;
    else return false;
}

void queue_push_back(Queue queue, int value) {// Добавление элемента в конец
    Node new_node = (Node)malloc(sizeof(*new_node)); // Резервируем память
    new_node->value = value;
    new_node->next_node = NULL;
    if (isempty(queue)) { // Если очередь ещё пуста
        queue->front = queue->last = new_node;
        return;
    }

    queue->last->next_node = new_node;
    queue->last = new_node;
    return;
}

Node queue_pop_front(Queue queue) {
    if (isempty(queue)) { // Если нет элементов в очереди
        printf("Очередь пуста!\n");
        return NULL;
    }

    Node temp = queue->front;
    queue->front = queue->front->next_node;
    printf("Вы удалили узел со значением %d\n",temp->value);
    return temp;
}

void print_queue(Queue queue) { // Вывод очереди
    if (isempty(queue)) {
        printf("Очередь пуста!\n");
        return;
    }

    printf("Oчередь:\n");
    Node this_node = queue->front;
    while (this_node->next_node) {
        printf("(%d), ", this_node->value);
        this_node = this_node->next_node;
    }

    printf("(%d).\n", this_node->value);
    return;
}


bool procedure(Queue queue) {
    if(isempty(queue)) {
        printf("Очередь пуста!\n");
        return false;
    }

    int index = 0, temp = 0, i = 0;
    Node this_node = queue->front;
    while (this_node->next_node) {
        if (this_node->value <= this_node->next_node->value) {
            this_node = this_node->next_node;
            index++;
        } else {
            index++;
            break;
        }
    }

    if(this_node == queue->last) {
        return false;
    }

    for(int j = 0; j <= index; j++) {
        this_node = queue->front;
        for (i=0; i <=index; i++){
            if (this_node->value <= this_node->next_node->value) {
                this_node = this_node->next_node;
            } else {
                break;
            }
        }
    
        if (i == index) {
            break;
        }

        if (this_node->next_node->value < this_node->value) {
            temp = this_node->next_node->value;
            this_node->next_node->value = this_node->value;
            this_node->value = temp;
        }

        index--;
    }
    return true;
}

void Insertsort(Queue queue) {
    while(procedure(queue)) {
        procedure(queue);
    }
}

void delete_queue(Queue queue) {// Освобождение памяти, занимаемой очередью
    if (isempty(queue)) {
        free(queue);
        return;
    }
     
    Node this_node = queue->front;
    Node temp; // Временная ссылка на узел
    while (this_node->next_node) {
        temp = this_node;
        this_node = this_node->next_node;
        //printf("Deleted node: %d\n", temp->value);
        free(temp); // Удаление по временной ссылке
    }
    temp = this_node;
    //printf("Deleted node: %d\n", temp->value);
    free(temp);
    free(queue);
    return;
}
