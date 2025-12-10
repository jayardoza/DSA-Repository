#include <stdio.h>
#include <stdbool.h>
#include "types.h"

// write your functions here
void initializeStack(Stack *s) {
    s->top = -1;
}

bool isFull(Stack *s) {
    if(s->top == MAX-1) return true;
    else return false;
}

bool isEmpty(Stack *s) {
    if(s->top == -1) return true;
    else return false;
}

void push(Stack *s, int value) {
    s->top++;
    s->items[s->top] = value;

}

int pop(Stack *s) {
    s->top--;
    return s->items[s->top + 1];

}

int peek(Stack *s) {
    return s->items[s->top];
}

int top(Stack *s) {
    return s->top;
}

void display(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
    } 
    else {
        int i;
        for (i = s->top; i >= 0; i--) {
            printf("%d\n", s->items[i]);
        }
    }
}
