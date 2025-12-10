#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

// initVHeap
void initVHeap(VHeap* V) {
    int i;
    for(i = 0; i < MAX_SIZE; i++) {
        if(i+1 == MAX_SIZE) V->H[i].next = -1;
        else V->H[i].next = i+1;
    }
}

// alloc
int alloc(VHeap* V) {
    int ret = V->avail;
    if(V->avail != -1) {
        V->avail = V->H[ret].next;
    }
    return ret;
}

// dealloc
void dealloc(VHeap* V, int index) {
    V->H[index].next = V->avail;
    V->avail = index;
}

// insertArticle
int insertArticle(VHeap* V, int* L, Article article, int pos) {
    int newCell = alloc(V);
    if(newCell != -1) {
        V->H[newCell].article = article;
        int* trav; 
        
        if(pos == -1) {
            V->H[newCell].next = -1;
            for(trav = L; *trav != -1; trav = &V->H[*trav].next);
            *trav = newCell;
        } else {
            int count;
            for(count = 0, trav = L; *trav != -1 && count < pos; trav = &V->H[*trav].next, ++count);
            V->H[newCell].next = *trav;
            *trav = newCell;
        }
        return 1;
    } 
    else {
        printf("Error: Heap is full. Cannot insert new article.\n");
        return 0;
    }
}

// viewArticles
void viewArticles(VHeap V, int L) {
    if(L != -1) {
        printf("\n--- List of Articles ---\n");
        for(;L != -1; L = V.H[L].next) printf("ID: %d | Title: %s\n", V.H[L].article.id, V.H[L].article.title);
        printf("------------------------\n\n");
    }
    else printf("The knowledge base is empty.\n");
}

// searchArticle
void searchArticle(VHeap V, int L, int id) {
    for(; V.H[L].next != -1 && V.H[L].article.id != id; L = V.H[L].next);
    if(V.H[L].article.id == id) {
        printf("\n--- Article Found ---\n");
        printf("ID: %d\n", V.H[L].article.id);
        printf("Title: %s\n", V.H[L].article.title);
        printf("Content: %s\n", V.H[L].article.content);
        printf("---------------------\n\n");
    }
    else printf("Article with ID %d not found.\n\n", id);
}
// deleteArticle
int deleteArticle(VHeap* V, int *L, int id) {
    int* trav;
    int temp;
    
    for(trav = L; *trav != -1 && V->H[*trav].article.id != id; trav = &V->H[*trav].next);
    if(V->H[*trav].article.id == id) {
        temp = *trav;
        *trav = V->H[*trav].next;
        dealloc(V, temp);
        printf("Article with ID %d deleted successfully.\n\n", id);
        return 1;
    } 
    else {
        printf("Article with ID %d not found.\n\n", id);
        return 0;
    }
    
}
