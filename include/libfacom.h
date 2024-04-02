#ifndef __LIBFACOM__
#define __LIBFACOM__

#include <stdint.h>
typedef struct {
    uintptr_t *vetor;
    int qtde_elementos;
    int tamanho_max;
    uintptr_t apagado;
    char *(*pegar_chave)(void *);
} thash; 

uint32_t hasher(const char *chave, uint32_t seed);
int inserir(thash *hash, void *bucket);
int construir(thash *hash, int nbuckets, char *(*pegar_chave)(void *));
void * buscar(thash hash, const char *chave);
int remover(thash *hash, const char *chave);
void deletar_hash(thash *hash);

/*É usado o unitptr_t pra definir um tipo dinâmico*/
/*Nas funções, é passado *hash pois o hash precisa ser alterado por referência. No buscar, não precisa disso, pois é enviado um elemento do tipo da struct*/

#endif