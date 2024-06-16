#ifndef __AVL__
#define __AVL__

typedef int titem;

typedef struct _node {
    titem item;
    struct _node *esq;
    struct _node *dir;
    int h;
} tnode;

// ele não perde o endereço da raíz da AVL pq a gnt lida com o endereço do ponteiro que aponta pra raíz. legal
// tudo que for alterar a estrutura da árvore, a gente passa o endereço
// a destruição da árvore n precisa passar o endereço pq a gnt quer liberar o ponteiro mesmo
void avl_insere(tnode ** parv, titem item);
void avl_remove(tnode ** parv, titem item);
void avl_destroi(tnode * parv);

void _re(tnode ** x);
void _rd(tnode ** x);
void _rebalanceia(tnode ** parv);

#endif