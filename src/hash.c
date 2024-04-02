#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/libfacom.h"
#define SEED 0x12345678

// ?
uint32_t hasher(const char *chave, uint32_t seed) {
    for (; *chave; ++chave)  {
        seed ^= *chave;
        seed *= 0x5bd1e995;
        seed ^= seed >> 15;
    }
    return seed;
}

int inserir(thash *hash, void *bucket) {
    uint32_t hashNum = hasher(hash->pegar_chave(bucket), SEED);
    int pos = hashNum % (hash->tamanho_max);

    if(hash->qtde_elementos + 1 == hash->tamanho_max) {
        free(bucket);
        return EXIT_FAILURE;
    } else {
        while(hash->vetor[pos] != 0 || hash->vetor[pos] == hash->apagado) {
            pos = (pos + 1) % hash->tamanho_max;
        }

        hash->vetor[pos] = (uintptr_t) bucket;
        hash->qtde_elementos += 1;
    }

    return EXIT_SUCCESS;
}

int construir(thash *hash, int nbuckets, char *(*pegar_chave)(void *)) {
    hash->vetor = calloc(sizeof(void *), nbuckets + 1);

    if(hash->vetor == NULL) {
        return EXIT_FAILURE;
    }

    hash->pegar_chave = pegar_chave;
    hash->qtde_elementos = 0;
    hash->tamanho_max = nbuckets + 1;

    // Poderia ser qualquer endereço de variável, já que temos certeza que o endereço dela não estará na struct
    hash->apagado = (uintptr_t) &(hash->qtde_elementos);
}

// As condições são usadas para verificar quando apagar pois não é necessário liberar memória se a memória não foi requisitada
void deletar_hash(thash *hash) {
    for(int i = 0; i < hash->tamanho_max; i++) {
        if(hash->vetor[i] != 0) 
            if(hash->vetor[i] != hash->apagado)
                free((void *) hash->vetor[i]);
    }

    free(hash->vetor);
}

void * buscar(thash hash, const char *chave) {

}

int remover(thash *hash, const char *chave) {

}
