#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"

// write your functions here
Queue* initialize() {
    Queue* Q = malloc(sizeof(Queue));
    Q->front = -1;
    Q->rear = -1;
    Q->list.count = 0;
    
    return Q;
}

void enqueue(Queue* q, int value) {
    if(q->front == -1 && q->rear == -1) {
        q->front++;
        q->rear++;
    } 
    else q->rear = ((q->rear + 1) % MAX);
    
    q->list.items[q->rear] = value;
    q->list.count++;
}

int dequeue(Queue* q) {
    q->front = ((q->front + 1) % MAX);
    q->list.count--;
    
    return (q->list.items[(q->front - 1 + MAX) % MAX]);
}

bool isFull(Queue* q) {
    if(q->list.count == MAX) return true;
    else return false;
}

bool isEmpty(Queue* q) {
    if(q->list.count == 0) return true;
    else return false;
}

void display(Queue* q) {
    if(isEmpty(q)) printf("Queue is empty.");
    else {
        int trav, i;
        for(i = q->front, trav = 0; trav < q->list.count; i = ((i + 1) % MAX), trav++) {
            printf("%d ", q->list.items[i]);
        }
    }
    printf("\n");
}
