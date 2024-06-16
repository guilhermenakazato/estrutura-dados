#include "./avl.h"
#include <stdlib.h>
#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int altura(tnode * arv) {
    if(arv == NULL) {
        return -1;
    } 
    
    return arv->h;
}

void avl_insere(tnode ** parv, titem item) {
    if(*parv == NULL) {
        *parv = (tnode *) malloc(sizeof(tnode));
        (*parv)->dir = NULL;
        (*parv)->esq = NULL;
        (*parv)->item = item;

        // altura 0 pois é folha (pelo menos até o momento, dps rebalanceia pra ver se ta certo)
        (*parv)->h = 0;
    } else {
        int comp = (*parv)->item - item;

        if (comp > 0) {
            avl_insere(&(*parv)->esq, item);
        } else {
            avl_insere(&(*parv)->dir, item);
        }
    }

    // adicionou uma folha, então a raiz tem que aumentar em um o tamanho e aí rebalancear tudo pra ver se tá certo
    (*parv)->h = max(altura((*parv)->dir), altura((*parv)->esq)) + 1;
    _rebalanceia(parv);
}

tnode *acha_sucessor(tnode **arv) {
    if((*arv)->esq == NULL) {
        return *arv;
    } else {
        acha_sucessor(&(*arv)->esq);
    }
}

void avl_remove(tnode ** parv, titem item) {
    int cmp;

    if(*parv != NULL) {
        cmp = (*parv)->item - item;

        if(cmp > 0) {
            avl_remove(&(*parv)->esq, item);
        } else if(cmp < 0) {
            avl_remove(&(*parv)->dir, item);
        } else {
            if((*parv)->esq == NULL && (*parv)->dir == NULL) {
                // folha, então apenas remove tudo
                free(*parv);
                *parv = NULL;
            } else if((*parv)->esq == NULL || (*parv)->dir == NULL) {
                // tem um filho, então promove ele
                tnode *aux  = *parv;

                if((*parv)->esq == NULL) {
                    *parv = (*parv)->dir;
                } else {        
                    *parv = (*parv)->esq;
                }

                free(aux);
            } else {
                // tem dois filhos, então troca pelo valor do sucessor e remove ele recursivamente
                // mandando primeiro o filho esq pra poder achar recursivo o sucessor
                tnode *sucessor = acha_sucessor(&(*parv)->dir);
                (*parv)->item = sucessor->item;

                // aqui a gente tem certeza que tem dois elementos repetidos, o sucessor e o que foi removido
                // então a gente chama remoção no sucessor
                // porém... se chamar remoção na árvore e tem dois repetidos, vai dar erro, não?
                // não, pois aqui a gente chama a remoção na sub-arvore q o sucessor tava :) smort
                avl_remove(&(*parv)->dir, sucessor->item);
            }
        }

        // só rebalanceie se tiver removido uma não folha
        // vc não pode aumentar a altura da folha e não tem o que rebalancear nela já q ela n tem filhos se ela foi removida
        if(*parv != NULL) {
            (*parv)->h = max(altura((*parv)->dir), altura((*parv)->esq)) + 1;
            _rebalanceia(parv);
        }   
    }
}

// pós-ordem
void avl_destroi(tnode * parv) {
    if(parv != NULL) {
        avl_destroi(parv->esq);
        avl_destroi(parv->dir);
        free(parv);
    }
}

// fica mais fácil de fazer as rotações se vc desenhar elas em algum lugar
// lembre-se que tem que modificar a altura tb
void _re(tnode ** parv) {
    tnode *x = *parv;
    tnode *y = x->dir;
    tnode *A = x->esq;
    tnode *B = y->esq;  
    tnode *C = y->dir;

    y->esq = x;
    x->dir = B;
    *parv = y;

    // altura de y = altura de (x ou C) + 1
    // altura de x = altura de (A ou B) + 1
    // se fizer o desenho, fica mais fácil de entender o pq
    x->h = max(altura(A), altura(B)) + 1;
    y->h = max(altura(x), altura(C)) + 1;
}

void _rd(tnode ** parv) {
    tnode *y = *parv;
    tnode *x = y->esq;
    tnode *A = x->esq;
    tnode *B = x->dir;
    tnode *C = y->dir;

    x->dir = y;
    y->esq = B;
    *parv = x;

    // altura x = altura de (A ou y) + 1
    // altura y = altura de (B ou C) + 1
    // se fizer o desenho, fica mais fácil de entender o pq
    y->h = max(altura(B), altura(C)) + 1;
    x->h = max(altura(A), altura(y)) + 1;
}

void _rebalanceia(tnode ** parv) {
    int fb;
    int fbf;
    tnode *filho;
    fb = altura((*parv)->esq) - altura((*parv)->dir);

    // a rotação é pra esquerda, mas tem que pegar da direita (-->)
    if(fb == -2) {
        filho = (*parv)->dir;
        fbf = altura(filho->esq) - altura(filho->dir);

        // dois negativos significa que é (--> ->), então faz RE no pai apenas
        if(fbf <= 0) {  
            _re(parv);
        } else {    
            // (--> <-), faz RD no filho e RE no pai
            _rd(&(*parv)->dir);
            _re(parv);
        }
    // a rotação é pra direita, mas tem que pegar da esquerda (<--)
    } else if(fb == 2) {    
        filho = (*parv)->esq;
        fbf = altura(filho->esq) - altura(filho->dir);

        // (<-), então faz RD no pai apenas
        if(fbf >= 0) {
            _rd(parv);
        } else {
            // caso <-- ->, então faz RE no filho e RD no pai
            _re(&(*parv)->esq); // é importante passar a variável parv e não a filho pq senão vai alterar a cópia, e não a referência
            _rd(parv);
        }
    }
} 