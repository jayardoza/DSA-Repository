// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int top;
}Stack;

Stack* initialize() {
    Stack* s = malloc(sizeof(Stack));
    s->top = -1;
    return s;
}

bool isFull(Stack* s) {
    if(s->top == MAX-1) return true;
    else return false;
}

bool isEmpty(Stack* s) {
    if(s->top == -1) return true;
    else return false;
}

void push(Stack* s, int data) {
    if(s->top == MAX-1) printf("S = is full\n");
    else {
        s->top++;
        s->items[s->top] = data;
    }
}

int pop(Stack* s) {
    if(s->top == -1) return -1;
    else {
        s->top--;
        return s->items[s->top+1];
    }
}

int peek(Stack* s) {
    if(s->top == -1) return s->top;
    else return s->items[s->top];
}

void display(Stack* s) {
    if(s->top == -1) printf("S = is empty\n");
    else {
        printf("\nS = ");
        int i;
        for(i = 0; i <= s->top; i++) printf("%d ", s->items[i]);
    }
}

int main() {
    Stack* S = initialize();
    printf("isFull = %d\n", isFull(S));
    printf("isEmpty = %d\n", isEmpty(S));
    push(S, 5);
    push(S, 4);
    push(S, 3);
    printf("Pop = %d", pop(S));
    display(S);
    push(S, 2);
    display(S);
    printf("\n%d", peek(S));

    return 0;
}
