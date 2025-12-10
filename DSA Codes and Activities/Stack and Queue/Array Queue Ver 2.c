#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

Queue* initialize();
bool isEmpty(Queue* q);
bool isFull(Queue* q);
bool enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);
int getSacrificialSpace(Queue* q);

Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    q->front = 1;  
    q->rear = 0;   
    return q;
}

bool isEmpty(Queue* q) {
    return q->front == (q->rear + 1) % MAX;
}


bool isFull(Queue* q) {
    return q->front == (q->rear + 2) % MAX;
}


int getSacrificialSpace(Queue* q) {

    return (q->front - 1 + MAX) % MAX;
}

bool enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow! Cannot enqueue %d\n", value);
        return false;
    }
    
    q->rear = (q->rear + 1) % MAX;
    
    q->items[q->rear] = value;
    
    printf("Enqueued %d. Front=%d, Rear=%d\n", value, q->front, q->rear);
    return true;
}

int dequeue(Queue* q) {
  
    if (isEmpty(q)) {
        printf("Queue Underflow! Cannot dequeue from empty queue\n");
        return -1;  
    }
    
    
    int value = q->items[q->front];
    
    q->front = (q->front + 1) % MAX;
    
    printf("Dequeued %d. Front=%d, Rear=%d\n", value, q->front, q->rear);
    return value;
}

int front(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! No front element.\n");
        return -1;
    }
    
    return q->items[q->front];
}


void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    
    printf("Queue contents: ");
    
    int i = q->front;
    while (true) {
        printf("%d ", q->items[i]);
        
        if (i == q->rear) {
            break;
        }
        
        i = (i + 1) % MAX;
    }
    
    printf("\n");
    printf("Front index: %d, Rear index: %d\n", q->front, q->rear);
    printf("Sacrificial space index: %d\n", getSacrificialSpace(q));
}

int main() {
    Queue* myQueue = initialize();
    
    printf("=== Queue Implementation (Variation 2 - With Sacrificial Space) ===\n\n");
    
    printf("Initial state:\n");
    display(myQueue);
    printf("Is empty: %s\n", isEmpty(myQueue) ? "true" : "false");
    printf("Is full: %s\n\n", isFull(myQueue) ? "true" : "false");
    
    printf("Enqueuing elements 10 to 80:\n");
    for (int i = 10; i <= 80; i += 10) {
        enqueue(myQueue, i);
    }
    display(myQueue);
    printf("Is empty: %s, Is full: %s\n\n", 
           isEmpty(myQueue) ? "true" : "false", 
           isFull(myQueue) ? "true" : "false");
    
    printf("Trying to enqueue 90 (queue should be full):\n");
    enqueue(myQueue, 90);
    printf("\n");
    
    printf("Dequeuing 3 elements:\n");
    for (int i = 0; i < 3; i++) {
        dequeue(myQueue);
    }
    display(myQueue);
    printf("\n");
    
    printf("Enqueuing 90 and 100:\n");
    enqueue(myQueue, 90);
    enqueue(myQueue, 100);
    display(myQueue);
    printf("Is full: %s\n\n", isFull(myQueue) ? "true" : "false");
    
    printf("Front element: %d\n\n", front(myQueue));
    
    printf("Enqueuing 110 (will wrap around):\n");
    enqueue(myQueue, 110);
    display(myQueue);
    printf("\n");
    
    printf("Dequeuing all elements:\n");
    while (!isEmpty(myQueue)) {
        dequeue(myQueue);
    }
    display(myQueue);
    printf("\n");
    
    printf("Trying to dequeue from empty queue:\n");
    dequeue(myQueue);
    
    free(myQueue);
    return 0;
}
