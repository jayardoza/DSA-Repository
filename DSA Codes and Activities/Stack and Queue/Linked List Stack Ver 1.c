#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==================== LINKED LIST STACK ====================

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

// Stack Operations
Stack* initializeStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

bool isFullStack(Stack* s) {
    return false;  // Linked list can never be full
}

bool isEmptyStack(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
    printf("Pushed %d to stack\n", value);
}

int pop(Stack* s) {
    if (isEmptyStack(s)) {
        printf("Stack underflow! Cannot pop.\n");
        return -1;
    }
    Node* temp = s->top;
    int value = temp->data;
    s->top = s->top->next;
    free(temp);
    return value;
}

int peek(Stack* s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty! Cannot peek.\n");
        return -1;
    }
    return s->top->data;
}

void displayStack(Stack* s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack (top to bottom): ");
    Node* temp = s->top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    printf("========== STACK DEMONSTRATION ==========\n");
    Stack* s = initializeStack();
    
    push(s, 1);
    push(s, 3);
    push(s, 5);
    displayStack(s);
    
    push(s, 4);
    displayStack(s);
    
    printf("Peek: %d\n", peek(s));
    printf("Popped: %d\n", pop(s));
    displayStack(s);
}
