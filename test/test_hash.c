#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/libfacom.h"

typedef struct {
    char nome[30];
    char cpf[11];
} taluno;

char *get_key(void *reg) {
    return ((taluno *)reg)->nome;
}

void *aloca_aluno(char *nome, char *cpf) {
    taluno *aluno = malloc(sizeof(taluno));
    strcpy(aluno->nome, nome);
    strcpy(aluno->cpf, cpf);
    return aluno;
}

void test_insere() {
    thash h;
    int nbuckets = 10;

    construir(&h, nbuckets, get_key);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_FAILURE);
    deletar_hash(&h);
}

void test_search() {
    thash h;
    int nbuckets = 10;
    taluno *aluno;
    construir(&h, nbuckets, get_key);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("takashi", "1123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("matsubara", "2123456789")) == EXIT_SUCCESS);

    aluno = buscar(h, "edson");
    assert(aluno->cpf[0] == '0');
    aluno = buscar(h, "takashi");
    assert(aluno->cpf[0] == '1');
    aluno = buscar(h, "matsubara");
    assert(aluno->cpf[0] == '2');
    aluno = buscar(h, "patricia");
    assert(aluno == NULL);

    deletar_hash(&h);
}

void test_remove() {
    thash h;
    int nbuckets = 10;
    taluno *aluno;
    construir(&h, nbuckets, get_key);
    assert(inserir(&h, aloca_aluno("edson", "0123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("takashi", "1123456789")) == EXIT_SUCCESS);
    assert(inserir(&h, aloca_aluno("matsubara", "2123456789")) == EXIT_SUCCESS);

    aluno = buscar(h, "edson");
    assert(aluno->cpf[0] == '0');
    aluno = buscar(h, "takashi");
    assert(aluno->cpf[0] == '1');
    aluno = buscar(h, "matsubara");
    assert(aluno->cpf[0] == '2');
    aluno = buscar(h, "patricia");
    assert(aluno == NULL);

    assert(h.qtde_elementos == 3);
    assert(remover(&h, "edson") == EXIT_SUCCESS);
    aluno = buscar(h, "edson");
    assert(aluno == NULL);
    assert(h.qtde_elementos == 2);

    assert(remover(&h, "edson") == EXIT_FAILURE);

    aluno = buscar(h, "matsubara");
    assert(aluno->cpf[0] == '2');

    deletar_hash(&h);
}

int main(int argc, char *argv[]) {
    test_insere();
    // test_search();
    // test_remove();
    return 0;
}