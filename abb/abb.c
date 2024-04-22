#include <stdlib.h>
#include "./abb.h"

void constroi(ttree *tree, int (*cmp)(void *, void *)) {
    tree->raiz = NULL;
    tree->cmp = cmp;
}

/* aqui atual é ponteiro para ponteiro pois, na estrutura ttree, ela aponta para um tnode. 
* Isso, por si só, já retorna um endereço, então tem que ser ponteiro. 
* Entretanto, precisamos também alterar essas estruturas para todos os lugares que acessam ela. 
* Então, ao invés de simplesmente passar uma cópia, você passa o ponteiro por referência.
*/

int insercao(ttree *tree, tnode **atual, void *node) {
    if(*atual == NULL) {
        *atual = malloc(sizeof(tnode));
        (*atual)->reg = node;
        (*atual)->esq = NULL;
        (*atual)->dir = NULL;
    } else {
        int resultadoComp = tree->cmp((*atual)->reg, node);

        if(resultadoComp < 0) {
            insercao(tree, &(*atual)->dir, node);
        } else {
            insercao(tree, &(*atual)->esq, node);
        }

        // lembre-se que esq é apenas um ponteiro normal, então para mandar o ponteiro pro ponteiro, mandamos o endereço
        // e isso ajuda também pois passa por referência, que é exatamente o que precisamos
    }
}

// Aqui, não precisamos alterar a estrutura da árvore, então passamos apenas uma cópia dos nós
void * busca(ttree *tree, tnode *atual, void *node) {
    if(atual == NULL) {
        // árvore vazia
        return NULL;
    } else {
        int resultadoComp = tree->cmp(atual->reg, node);

        if(resultadoComp == 0) {
            // nó atual = nó que você tá buscando, então retornar nó atual
            return atual->reg;
        } else if(resultadoComp < 0) {
            // se o atual for menor do que o que você quer inserir, então vai para a direita
            busca(tree, atual->dir, node);
        } else {
            // se o atual for maior do que o que você quer inserir, então vai para a esquerda
            busca(tree, atual->esq, node);
        }
    }

}