#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==================== LINKED LIST QUEUE VARIATION 2 ====================
// Front points to last node, Rear points to first node

typedef struct Queue2 {
    Node* front;  // Points to last node
    Node* rear;   // Points to first node
} Queue2;

// Queue2 Operations
Queue2* initializeQueue2() {
    Queue2* q = (Queue2*)malloc(sizeof(Queue2));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

bool isFullQueue2(Queue2* q) {
    return false;  // Linked list can never be full
}

bool isEmptyQueue2(Queue2* q) {
    return q->rear == NULL;  // rear points to first node
}

void enqueue2(Queue2* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    
    if (isEmptyQueue2(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->front->next = newNode;
        q->front = newNode;
    }
    printf("Enqueued %d to queue (Variation 2)\n", value);
}

int dequeue2(Queue2* q) {
    if (isEmptyQueue2(q)) {
        printf("Queue underflow! Cannot dequeue.\n");
        return -1;
    }
    Node* temp = q->rear;
    int value = temp->data;
    q->rear = q->rear->next;
    
    if (q->rear == NULL) {
        q->front = NULL;
    }
    
    free(temp);
    return value;
}

int front2(Queue2* q) {
    if (isEmptyQueue2(q)) {
        printf("Queue is empty! Cannot get front.\n");
        return -1;
    }
    return q->rear->data;  // rear points to first node
}

void displayQueue2(Queue2* q) {
    if (isEmptyQueue2(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue (front to rear): ");
    Node* temp = q->rear;  // Start from rear (first node)
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}



int main(){
	printf("\n========== QUEUE VARIATION 2 DEMONSTRATION ==========\n");
    printf("(Front -> Last Node, Rear -> First Node)\n");
    Queue2* q2 = initializeQueue2();
    
    enqueue2(q2, 1);
    enqueue2(q2, 3);
    enqueue2(q2, 5);
    displayQueue2(q2);
    
    enqueue2(q2, 4);
    displayQueue2(q2);
    
    printf("Front: %d\n", front2(q2));
    printf("Dequeued: %d\n", dequeue2(q2));
    displayQueue2(q2);
}
