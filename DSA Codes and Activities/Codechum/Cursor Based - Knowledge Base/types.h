#ifndef TYPES_H
#define TYPES_H

typedef struct {
    int id;
    char title[64];
    char content[255];
} Article;

typedef struct {
    Article article;
    int next;
} Cell;

#define MAX_SIZE 20

typedef Cell HeapSpace[MAX_SIZE];

typedef struct {
    HeapSpace H;
    int avail;
} VHeap;

// function prototypes
void initVHeap(VHeap *);
int alloc(VHeap *);
void dealloc(VHeap *, int);
int insertArticle(VHeap *, int *, Article, int);
void viewArticles(VHeap, int);
void searchArticle(VHeap, int, int);
int deleteArticle(VHeap *, int *, int);

#endif
