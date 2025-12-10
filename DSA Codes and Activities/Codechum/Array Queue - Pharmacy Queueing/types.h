#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int count;
} List;

typedef struct {
    List list;
    int front;
    int rear;
} Queue;

Queue* initialize();
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void display(Queue* q);

#endif
