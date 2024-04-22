#ifndef __ABB__
#define __ABB__

typedef struct _no {
    void * reg;
    struct _no *esq;
    struct _no *dir;
} tnode;

typedef struct {
    tnode *raiz;

    // número positivo, zero e negativo quando a > b, a == b e a < b respectivamente.
    int (*cmp)(void *, void *);
} ttree;

int insercao(ttree *tree, tnode **atual, void *node);
void * busca(ttree *tree, tnode *atual, void *node);
void constroi(ttree *tree, int (*cmp)(void *, void *));

#endif