#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int count;
}List;

typedef struct {
    List list;
    int front;
    int rear;
}Queue;

Queue* initialize() {
    Queue* Q = malloc(sizeof(Queue));
    Q->list.count = 0;
    Q->front = Q->rear = -1;
    
    return Q;
}

bool isFull(Queue* q) {
    if(q->list.count == MAX) return true;
    else return false;
}

bool isEmpty(Queue* q) {
    if(q->list.count == 0) return true;
    else return false;
}

void enqueue(Queue* q, int value) {
    if(isFull(q)) {
        printf("Q = is full");
        return;
    }
    else if(isEmpty(q)) {
        q->front = q->rear += 1;
    }
    else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->list.items[q->rear] = value;
    q->list.count++;
}

int dequeue(Queue* q) {
    if(isEmpty(q)) return -1;
    else {
        q->front = (q->front + 1) % MAX;
        q->list.count--;
        return q->list.items[(q->front - 1 + MAX) % MAX];
    }
}

int front(Queue* q) {
    if(isEmpty(q)) return -1;
    else return q->front;
    
}

void display(Queue* q) {
    int i, x;
    printf("\nQ = ");
    for(i = q->front, x =0; x != q->list.count; i = (i+1)%MAX, x++) {
        printf("%d ", q->list.items[i]);
    }
}


int main() {
    Queue* Q = initialize();
    printf("%d\n", isFull(Q));
    printf("%d\n", isEmpty(Q));
    enqueue(Q, 213);
    enqueue(Q, 53);
    enqueue(Q, 67);
    enqueue(Q, 547);
    enqueue(Q, 5237);
    enqueue(Q, 234);
    enqueue(Q, 643);
    enqueue(Q, 985);
    enqueue(Q, 811);
    enqueue(Q, 9787);
    display(Q);
    printf("\nDequeue value = %d", dequeue(Q));
    printf("\nDequeue value = %d", dequeue(Q));
    printf("\nDequeue value = %d", dequeue(Q));
    printf("\nDequeue value = %d", dequeue(Q));
    display(Q);
    enqueue(Q, 23);
    enqueue(Q, 53);
    display(Q);
    printf("\nDequeue value = %d", dequeue(Q));
    printf("\nDequeue value = %d", dequeue(Q));
    printf("\nDequeue value = %d", dequeue(Q));
    printf("\nDequeue value = %d", dequeue(Q));
    printf("\nDequeue value = %d", dequeue(Q));
    printf("\nFront = %d", front(Q));
    display(Q);
    printf("\nDequeue value = %d", dequeue(Q));
    display(Q);
    printf("\nFront = %d", front(Q));
    printf("\nDequeue value = %d", dequeue(Q));
    printf("\nFront = %d", front(Q));
    display(Q);

    return 0;
}
