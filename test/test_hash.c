#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/libfacom.h"

typedef struct {
    char nome[30];
    char cpf[11];
} taluno;

/*
Caso queira fazer pras infos de um carro
typedef struct {
    char placa[10];
    char modelo[30];
    char marca[30];
    char nome_motorista[30];
} tcarro;

char *get_key_placa(void *reg) {
    return ((tcarro *)reg)->placa;

    return (*((tcarro *) reg)).placa;
    o mais interno -> type casting
    o * do meio -> pega o conteúdo do ponteiro
} 

Sempre que trabalha com as structs, precisa de uma espécie de construtor, e é por isso que foi implementado o hash_constroi no hash.c. Basicamente, ele tenta fazer a alocação e você tem que zerar a estrutura com o calloc para determinar se a estrutura está vazia ou não. Com malloc, vai ter lixo e vai ter bagunça, pois o programa vai pensar que é um ponteiro e vai dar tudo errado.

No construtor, você manda o endereço da variável para deleted pois você tem certeza que o calloc não vai pegar o endereço da variável.
*/

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
    test_search();
    test_remove();
    return 0;
}
