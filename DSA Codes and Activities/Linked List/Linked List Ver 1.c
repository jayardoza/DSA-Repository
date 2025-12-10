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

List initialize() {
    List L;
    L.head = NULL;
    L.count = 0;
    return L;
}

List insertFirst(List list, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list.head;
    list.head = newNode;
    list.count++;
    return list;
}

List empty(List list) {
    Node *trav;
    Node* temp;
    for(trav = list.head; list.head != NULL; trav = list.head) {
        temp = trav;
        list.head = temp->next;
        free(temp);
        list.count--;
    }
    return list;
}

List insertLast(List list, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if(list.head == NULL) list.head = newNode;
    else {
        Node* current;
        for(current = list.head; current->next != NULL; current = current->next);
        current->next = newNode;
    }
    list.count++;
    return list;
}

List insertPos(List list, int data, int index) {
    if(index == 0) list = insertFirst(list, data);
    else if(index == list.count) list = insertLast(list, data);
    else {
        Node* newNode = malloc(sizeof(Node));
        Node* current;
        newNode->data = data;
        int i;
        for(current = list.head, i = 0; i < index-1; current = current->next, i++);
        newNode->next = current->next;
        current->next = newNode;
        list.count++;
    }
    return list;
}

List deleteStart(List list) {
    Node* current = list.head;
    list.head = current->next;
    free(current);
    list.count--;
    return list;
}

List deleteLast(List list) {
    Node* current;
    Node* temp;
    for(current = list.head; current->next->next != NULL; current = current->next);
    temp = current->next;
    current->next = NULL;
    free(temp);
    list.count--;
    return list;
}

List deletePos(List list, int index) {
    if(index == 0) list = deleteStart(list);
    else if(index == list.count-1) list = deleteLast(list);
    else {
        Node* current;
        Node* temp;
        int i;
        for(current = list.head, i = 0; i < index-1; current = current->next, i++);
        temp = current->next;
        current->next = temp->next;
        free(temp);
        list.count--;
    }
    return list;
}

int retrieve(List list, int index) {
    if(index >= 0 && index < list.count) {
        Node* current;
        int i;
        for(current = list.head, i = 0;i < index && current->next != NULL; current = current->next, i++);
        return current->data;
    }
    else return -1;
}

int locate(List list, int data) {
    if(list.head == NULL) return -1;
    Node* current;
    int i;
    for(current = list.head, i = 0; current->data != data && current->next != NULL; current = current->next, i++);
    if(current->data == data) return i;
    else return -1;
}

void display(List list) {
    Node* current;
    printf("\nCount = %d\nL = ", list.count);
    for(current = list.head; current != NULL; current = current->next) printf("%d ", current->data);
}

void main() {
    List L;
    L = initialize();
    L = insertFirst(L, 51);
    L = insertLast(L, 43);
    display(L);
    L = insertPos(L, 21, 0);
    display(L);
    L = empty(L);
    display(L);
    L = insertFirst(L, 51);
    L = insertLast(L, 43);
    L = insertFirst(L, 23);
    L = insertLast(L, 56);
    display(L);
    L = deleteStart(L);
    display(L);
    L = deleteLast(L);
    display(L);
    L = insertFirst(L, 23);
    L = insertLast(L, 56);
    display(L);
    L =deletePos(L, 3);
    display(L);
    printf("\n%d", retrieve(L, 2));
    printf("\n%d", locate(L, 43));
    
}
