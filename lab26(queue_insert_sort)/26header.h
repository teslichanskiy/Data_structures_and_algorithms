#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node *Node;
typedef struct _queue *Queue;

Queue create_queue();
int getsize(Queue queue);
bool isempty(Queue queue);
void queue_push_back(Queue queue, int value);
Node queue_pop_front(Queue queue);
void print_queue(Queue queue);
bool procedure(Queue queue);
void Insertsort(Queue queue);
void delete_queue(Queue queue);

#endif
