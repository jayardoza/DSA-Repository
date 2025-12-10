// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
}Node;

typedef struct {
    Node* head;
    int count;
}List;

List *initialize() {
    List *L = malloc(sizeof(List));
    if(L==NULL) return NULL;
    L->head = NULL;
    L->count = 0;
    return L;
}

void empty(List* list) {
    Node* trav;
    Node* temp;
    for(trav = list->head; trav != NULL; trav = list->head) {
        temp = list->head;
        list->head = temp->next;
        free(temp);
        list->count--;
    }
}

void insertFirst(List* list, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->count++;
}

void insertLast(List* list, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if(list->head == NULL) list->head = newNode;
    else {
        Node* current;
        for(current = list->head; current->next != NULL; current = current->next);
        current->next = newNode;
    }
    list->count++;
}

void insertPos(List* list, int data, int index) {
    if(index == 0) insertFirst(list, data);
    else if(index == list->count) insertLast(list, data);
    else {
        int i;
        Node* newNode = malloc(sizeof(Node));
        newNode->data = data;
        Node* current;
        for(current = list->head, i = 0; i < index-1; i++, current = current->next);
        newNode->next = current->next;
        current->next = newNode;
        list->count++;
    }
}

void deleteStart(List* list) {
    Node* temp;
    temp = list->head;
    list->head = temp->next;
    free(temp);
    list->count--;
}

void deleteLast(List* list) {
    Node* temp;
    Node* current;
    for(current = list->head; current->next->next != NULL; current = current->next);
    temp = current->next;
    current->next = NULL;
    free(temp);
    list->count--;
}

void deletePos(List* list, int index) {
    if(index == 0) deleteStart(list);
    else if(index == list->count-1) deleteLast(list);
    else {
        Node* temp;
        Node* current;
        int i;
        for(current = list->head, i = 0;i < index-2; i++, current = current->next);
        temp = current->next;
        current->next = temp->next;
        free(temp);
        list->count--;
    }
}

int retrieve(List* list, int index) {
    if(index >= 0 && index < list->count) {
        Node* current = malloc(sizeof(Node));
        int i;
        for(current = list->head, i = 0; i < index; current = current->next, i++);
        return current->data;
    }
    else return -1;
}

int locate(List* list, int data) {
    if(list->head == NULL) return -1;
    int i;
    Node* current;
    for(current = list->head, i = 0; current->data != data && current->next != NULL; current = current->next, i++);
    if(current->data == data) return i;
    else return -1;
}

void display(List* list) {
    Node *current = malloc(sizeof(Node));
    printf("\nCount = %d\nL = ", list->count);
    for(current = list->head; current != NULL; current = current->next) printf("%d ", current->data);
}


void main() {
    List* L = initialize();
    insertFirst(L, 17);
    insertFirst(L, 18);
    insertFirst(L, 19);
    display(L);
    insertLast(L, 23);
    display(L);
    insertPos(L, 2, 3);
    display(L);
    empty(L);
    display(L);
    insertFirst(L, 19);
    insertFirst(L, 215);
    insertFirst(L, 436);
    insertFirst(L, 125);
    insertFirst(L, 23);
    display(L);
    deleteStart(L);
    display(L);
    deleteLast(L);
    display(L);
    deletePos(L, 1);
    display(L);
    insertFirst(L, 41);
    insertFirst(L, 28);
    insertFirst(L, 11);
    display(L);
    printf("\n%d", retrieve(L, 0));
    printf("\n%d", locate(L, 213));
    
}
