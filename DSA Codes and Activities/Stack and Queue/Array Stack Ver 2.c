#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int top;
} Stack;

Stack* initialize();
bool isFull(Stack* s);
bool isEmpty(Stack* s);
bool push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
void display(Stack* s);

Stack* initialize() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    s->top = MAX; 
    return s;
}


bool isFull(Stack* s) {
    return s->top == 0; 
}


bool isEmpty(Stack* s) {
    return s->top == MAX;  
}


bool push(Stack* s, int value) {
 
    if (isFull(s)) {
        printf("Stack Overflow! Cannot push %d\n", value);
        return false;
    }
    
  
    s->top--;
    
    s->items[s->top] = value;
    
    return true;
}

int pop(Stack* s) {
   
    if (isEmpty(s)) {
        printf("Stack Underflow! Cannot pop from empty stack\n");
        return -1; 
    }
    
    int value = s->items[s->top];
    
    s->top++;
    
    return value;
}

int peek(Stack* s) {

    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    
    return s->items[s->top];
}

void display(Stack* s) {
    
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return;
    }
    
    printf("Stack contents (top to bottom): ");
    
    for (int i = s->top; i < MAX; i++) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
    printf("Current top index: %d\n", s->top);
}


int main() {
    Stack* myStack = initialize();
    
    printf("=== Stack Implementation (Variation 2) ===\n\n");
    
    printf("Initial state:\n");
    display(myStack);
    printf("Is empty: %s\n", isEmpty(myStack) ? "true" : "false");
    printf("Is full: %s\n\n", isFull(myStack) ? "true" : "false");
    
    
    printf("Pushing elements 10, 20, 30, 40, 50:\n");
    push(myStack, 10);
    push(myStack, 20);
    push(myStack, 30);
    push(myStack, 40);
    push(myStack, 50);
    display(myStack);
    
    printf("Peek at top: %d\n\n", peek(myStack));
    
    printf("Pushing more elements 60, 70, 80, 90, 100:\n");
    push(myStack, 60);
    push(myStack, 70);
    push(myStack, 80);
    push(myStack, 90);
    push(myStack, 100);
    display(myStack);
    printf("Is full: %s\n\n", isFull(myStack) ? "true" : "false");
    
    printf("Trying to push 110 (stack should be full):\n");
    push(myStack, 110);
    printf("\n");
    
    printf("Popping elements:\n");
    printf("Popped: %d\n", pop(myStack));
    printf("Popped: %d\n", pop(myStack));
    printf("Popped: %d\n", pop(myStack));
    display(myStack);
    
    printf("Pushing 95 after popping:\n");
    push(myStack, 95);
    display(myStack);
    
    printf("Popping all remaining elements:\n");
    while (!isEmpty(myStack)) {
        printf("Popped: %d\n", pop(myStack));
    }
    printf("\n");
    
    printf("Trying to pop from empty stack:\n");
    pop(myStack);
    
    free(myStack);
    return 0;
}
