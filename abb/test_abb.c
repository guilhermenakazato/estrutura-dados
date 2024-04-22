#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "./abb.h"

typedef struct {
    int rga;
    char nome[30];
} taluno;

int cmp(void *aluno1, void *aluno2) {
    return ((taluno *)aluno1)->rga - ((taluno *)aluno2)->rga;
}

taluno *aloca_aluno(int rga, char nome[]) {
    taluno *aluno = malloc(sizeof(taluno));
    aluno->rga = rga;
    strcpy(aluno->nome, nome);
    return aluno;
}

void test_compara() {
    taluno t1;
    taluno t2;
    taluno t3;
    taluno t4;
    t1.rga = 10;
    t2.rga = 20;
    t3.rga = 10;
    t4.rga = 5;
    assert(cmp(&t1, &t2) < 0);  /*t1 < t2*/
    assert(cmp(&t1, &t3) == 0); /* t1 == t2*/
    assert(cmp(&t1, &t4) > 0);  /*t1 > t2 */
}

void test_constroi() {
    ttree arv;
    constroi(&arv, cmp);
    assert(arv.raiz == NULL);
    taluno t1;
    taluno t2;
    taluno t3;
    taluno t4;
    t1.rga = 10;
    t2.rga = 20;
    t3.rga = 10;
    t4.rga = 5;
    assert(arv.cmp(&t1, &t2) < 0);  /*t1 < t2*/
    assert(arv.cmp(&t1, &t3) == 0); /* t1 == t2*/
    assert(arv.cmp(&t1, &t4) > 0);  /*t1 > t2 */
}

void test_insere() {
    taluno *no;
    ttree arv;

    no = aloca_aluno(10, "edson");
    constroi(&arv, cmp);
    insercao(&arv, &(arv.raiz), no);
    assert(((taluno *)arv.raiz->reg)->rga == 10);
    assert(arv.raiz->esq == NULL);
    assert(arv.raiz->dir == NULL);

    no = aloca_aluno(20, "takashi");
    insercao(&arv, &(arv.raiz), no);
    assert(((taluno *)arv.raiz->reg)->rga == 10);
    assert(arv.raiz->esq == NULL);
    assert(((taluno *)arv.raiz->dir->reg)->rga == 20);

    no = aloca_aluno(5, "matsubara");
    insercao(&arv, &(arv.raiz), no);
    assert(((taluno *)arv.raiz->reg)->rga == 10);
    assert(((taluno *)arv.raiz->dir->reg)->rga == 20);
    assert(((taluno *)arv.raiz->esq->reg)->rga == 5);
    assert(((taluno *)arv.raiz->dir->reg)->rga == 20);
}

void test_busca() {
    taluno *no;
    taluno *searchResult;
    int rga;
    ttree arv;
    constroi(&arv, cmp);
    
    no = aloca_aluno(10, "edson");
    insercao(&arv, &(arv.raiz), no);

    no = aloca_aluno(20, "takashi");
    insercao(&arv, &(arv.raiz), no);

    no = aloca_aluno(5, "matsubara");
    insercao(&arv, &(arv.raiz), no);

    searchResult->rga = 10;
    no = busca(&arv, arv.raiz, searchResult);
    assert(no->rga == searchResult->rga);

    searchResult->rga = 7;
    no = busca(&arv, arv.raiz, searchResult);
    assert(no == NULL);

    searchResult->rga = 5;
    no = busca(&arv, arv.raiz, searchResult);
    assert(no->rga == searchResult->rga);

    searchResult->rga = 20;
    no = busca(&arv, arv.raiz, searchResult);
    assert(no->rga == searchResult->rga);
}

int main() {
    test_compara();
    test_constroi();
    test_insere();
    test_busca();
    return EXIT_SUCCESS;
}