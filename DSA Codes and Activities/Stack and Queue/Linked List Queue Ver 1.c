#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==================== LINKED LIST QUEUE VARIATION 1 ====================
// Front points to first node, Rear points to last node

typedef struct Queue1 {
    Node* front;
    Node* rear;
} Queue1;

// Queue1 Operations
Queue1* initializeQueue1() {
    Queue1* q = (Queue1*)malloc(sizeof(Queue1));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

bool isFullQueue1(Queue1* q) {
    return false;  // Linked list can never be full
}

bool isEmptyQueue1(Queue1* q) {
    return q->front == NULL;
}

void enqueue1(Queue1* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    
    if (isEmptyQueue1(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("Enqueued %d to queue (Variation 1)\n", value);
}

int dequeue1(Queue1* q) {
    if (isEmptyQueue1(q)) {
        printf("Queue underflow! Cannot dequeue.\n");
        return -1;
    }
    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return value;
}

int front1(Queue1* q) {
    if (isEmptyQueue1(q)) {
        printf("Queue is empty! Cannot get front.\n");
        return -1;
    }
    return q->front->data;
}

void displayQueue1(Queue1* q) {
    if (isEmptyQueue1(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue (front to rear): ");
    Node* temp = q->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


int main(){
	 printf("\n========== QUEUE VARIATION 1 DEMONSTRATION ==========\n");
    printf("(Front -> First Node, Rear -> Last Node)\n");
    Queue1* q1 = initializeQueue1();
    
    enqueue1(q1, 1);
    enqueue1(q1, 3);
    enqueue1(q1, 5);
    displayQueue1(q1);
    
    enqueue1(q1, 4);
    displayQueue1(q1);
    
    printf("Front: %d\n", front1(q1));
    printf("Dequeued: %d\n", dequeue1(q1));
    displayQueue1(q1);
}
