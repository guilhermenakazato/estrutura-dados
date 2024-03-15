#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void imprimir_vetor(int vetor[], int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");
}

void troca(int *pos1, int *pos2) {
    int temp = *pos1;
    *pos1 = *pos2;
    *pos2 = temp;
}

int pai(int pos_filho) {
    return pos_filho == 0 ? 0 : (int) (pos_filho - 1) / 2;
}

int filho_esq(int pos_pai) {
    return pos_pai * 2 + 1;
}

int filho_dir(int pos_pai) {
    return pos_pai * 2 + 2;
}

void desce(int vetor[], int n, int tamanho_vetor) {
    int esquerdo = filho_esq(n);
    int direito = filho_dir(n);
    int maior = n;

    if(esquerdo < tamanho_vetor && vetor[esquerdo] > vetor[maior]) {
        maior = esquerdo;
    }
    
    if(direito < tamanho_vetor && vetor[direito] > vetor[maior]) {
        maior = direito;
    }

    if(maior != n) {
        troca(&vetor[maior], &vetor[n]);
        desce(vetor, maior, tamanho_vetor);
    }
}

void constroi_heap(int vetor[], int tamanho) {
    int pai_atual = pai(tamanho - 1);

    while(pai_atual >= 0) {
        desce(vetor, pai_atual, tamanho);
        pai_atual--;
    }
}

void sobe(int vetor[], int n) {
    int pos_pai = pai(n);

    if(vetor[n] > vetor[pos_pai]) {
        troca(&vetor[pos_pai], &vetor[n]);
        sobe(vetor, pos_pai);
    }
}

int acessa_max(int vetor[]) {
    return vetor[0];
}

int extrai_max(int vetor[], int *tam) {
    int max = vetor[0];
    vetor[0] = vetor[--*tam];

    desce(vetor, 0, *tam);
    return max;
}

void altera_prioridade(int vetor[], int tamanho, int n, int valor) {
    if(vetor[n] < valor) {
        vetor[n] = valor;
        sobe(vetor, n);
    } else {
        vetor[n] = valor;
        desce(vetor, n, tamanho);
    }
}

int insere_elemento(int vetor[], int *tamanho, int max, int valor) {
    if(*tamanho == max) {
        return EXIT_FAILURE;
    } else {
        vetor[*tamanho] = valor;
        ++*tamanho;

        sobe(vetor, *tamanho - 1);
        return EXIT_SUCCESS;
    }
}

void heap_sort(int vetor[], int tamanho) {
    constroi_heap(vetor, tamanho);

    while(tamanho > 0) {
        troca(&vetor[0], &vetor[--tamanho]);
        desce(vetor, 0, tamanho);
    }
}

void teste_pai() {
    int r;
    
    r = pai(6);
    assert(r == 2);

    r = pai(5);
    assert(r == 2);

    r = pai(0);
    assert(r == 0);
}

void teste_filho_esq() {
    int r;
    
    r = filho_esq(0);
    assert(r == 1);

    r = filho_esq(1);
    assert(r == 3);
    
    r = filho_esq(2);
    assert(r == 5);
}

void teste_filho_dir() {
    int r;

    r = filho_dir(0);
    assert(r == 2);

    r = filho_dir(1);
    assert(r == 4);

    r = filho_dir(2);
    assert(r == 6);
}

void teste_heap(int vetor[], int resposta[], int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        assert(vetor[i] == resposta[i]);
    }
}

void teste_constroi_heap() {
    int vetor[] = {1, 2, 3, 4, 5, 6, 7};
    int resposta[] = {7, 5, 6, 4, 2, 1, 3};
    constroi_heap(vetor, 7);
    teste_heap(vetor, resposta, 7);

    int vetor2[] = {6, 1, 3, 10, 5, 4, 7, 11, 9};
    int resposta2[] = {11, 10, 7, 9, 5, 4, 3, 1, 6};
    constroi_heap(vetor2, 9);
    teste_heap(vetor2, resposta2, 9);

    int array[7] = {1, 5, 3, 4, 10, 2, 0};
    int answer[7] = {10, 5, 3, 4, 1, 2, 0};
    constroi_heap(array, 7);
    teste_heap(array, answer, 7);

    int array2[3] = {1, 2, 3};
    int answer2[3] = {3, 2, 1};
    constroi_heap(array2, 3);
    teste_heap(array2, answer2, 3);

    int array3[7] = {7, 6, 5, 4, 3, 2, 1};
    int answer3[7] = {7, 6, 5, 4, 3, 2, 1};
    constroi_heap(array3, 7);
    teste_heap(array3, answer3, 7);

    int array4[7] = {10, 20, 5, 35, 50, 6, 100};
    int answer4[7] = {100, 50, 10, 35, 20, 6, 5};
    constroi_heap(array4, 7);
    teste_heap(array4, answer4, 7);
} 

void teste_sobe() {
    int array[3] = {8, 9, 10};
    sobe(array, 2);
    int answer[3] = {10, 9, 8};
    teste_heap(array, answer, 3);

    int array2[7] = {11, 9, 8, 20, 4, 2, 1};
    sobe(array2, 3);
    int answer2[7] = {20, 11, 8, 9, 4, 2, 1};
    teste_heap(array2, answer2, 7);

    int array3[7] = {25, 24, 23, 22, 21, 24, 19};
    sobe(array3, 5);
    int answer3[7] = {25, 24, 24, 22, 21, 23, 19};
    teste_heap(array3, answer3, 7);

    int array4[7] = {7, 6, 5, 4, 3, 2, 1};
    sobe(array4, 6);
    int answer4[7] = {7, 6, 5, 4, 3, 2, 1};
    teste_heap(array4, answer4, 7);

    int array5[4] = {3, 2, 1, 6};
    sobe(array5, 3);
    int answer5[4] = {6, 3, 1, 2};
    teste_heap(array5, answer5, 4);
}

void teste_desce() {
    int array[] = {1, 5, 3, 4, 10, 2, 0};
    desce(array, 1, 7);
    int answer[] = {1, 10, 3, 4, 5, 2, 0};
    teste_heap(array, answer, 7);

    int array2[7] = {9, 5, 8, 20, 4, 6, 3};
    desce(array2, 1, 7);
    desce(array2, 0, 7);
    int answer2[7] = {20, 9, 8, 5, 4, 6, 3};
    teste_heap(array2, answer2, 5);

    int array3[3] = {3, 2, 1};
    desce(array3, 0, 3);
    int answer3[3] = {3, 2, 1};
    teste_heap(array3, answer3, 3);

    int array4[7] = {7, 6, 5, 4, 3, 2, 10};
    desce(array4, 2, 7);
    int answer4[7] = {7, 6, 10, 4, 3, 2, 5};
    teste_heap(array4, answer4, 7);
}  

void teste_extrai_max() {
    int tamanho = 7;
    int array[] = {7, 5, 6, 4, 2, 1, 3};
    int resposta[] = {6, 5, 3, 4, 2, 1};
    extrai_max(array, &tamanho);
    teste_heap(array, resposta, tamanho);

    tamanho = 7;
    int array1[] = {20, 9, 8, 5, 4, 6, 3};
    int resposta1[] = {9, 5, 8, 3, 4, 6};
    extrai_max(array1, &tamanho);
    teste_heap(array1, resposta1, tamanho);

    tamanho = 3;
    int array2[] = {3, 2, 1};
    int resposta2[] = {2, 1};
    extrai_max(array2, &tamanho);
    teste_heap(array2, resposta2, tamanho);
}

void teste_altera_prioridade() {
    int vetor[3] = {100, 90, 70};
    int tam = 3;
    int n = 2;
    int valor = 101;
    altera_prioridade(vetor, tam, n, valor);
    int esperado[3] = {101, 90, 100};
    teste_heap(vetor, esperado, 3);

    int vetor2[3] = {101, 90, 100};
    int tam2 = 3;
    int n2 = 0;
    int valor2 = 70;
    altera_prioridade(vetor2, tam2, n2, valor2);
    int esperado2[3] = {100, 90, 70};
    teste_heap(vetor2, esperado2, 3);

    int vetor3[7] = {100, 90, 80, 70, 60, 50, 40};
    int tam3 = 7;
    int n3 = 4;
    int valor3 = 110;
    altera_prioridade(vetor3, tam3, n3, valor3);
    int esperado3[7] = {110, 100, 80, 70, 90, 50, 40};
    teste_heap(vetor3, esperado3, 7);

    int vetor4[7] = {100, 90, 80, 70, 60, 50, 40};
    int tam4 = 7;
    int n4 = 2;
    int valor4 = 30;
    altera_prioridade(vetor4, tam4, n4, valor4);
    int esperado4[7] = {100, 90, 50, 70, 60, 30, 40};
    teste_heap(vetor4, esperado4, 7);
}

void teste_insere_elemento() {
    int tamanho = 6;
    int tamanho_max = 7;
    int array[7] = {6, 5, 3, 4, 2, 1};
    int resposta[] = {6, 5, 3, 4, 2, 1, 2};

    assert(insere_elemento(array, &tamanho, tamanho_max, 2) == EXIT_SUCCESS);
    teste_heap(array, resposta, tamanho);
    assert(insere_elemento(array, &tamanho, tamanho_max, 2) == EXIT_FAILURE);

    tamanho = 3;
    tamanho_max = 4;
    int array1[4] = {3, 2, 1};
    int resposta1[] = {6, 3, 1, 2};  
    assert(insere_elemento(array1, &tamanho, tamanho_max, 6) == EXIT_SUCCESS);
    teste_heap(array1, resposta1, tamanho);

    tamanho = 6;
    tamanho_max = 7;
    int array2[7] = {6, 5, 3, 4, 2, 1};
    int resposta2[] = {7, 5, 6, 4, 2, 1, 3};
    assert(insere_elemento(array2, &tamanho, tamanho_max, 7) == EXIT_SUCCESS);
    teste_heap(array2, resposta2, tamanho); 
}

void teste_heap_sort() {
    int array[] = {3, 2, 1};
    int resposta[] = {1, 2, 3};
    heap_sort(array, 3);
    imprimir_vetor(array, 3);
    teste_heap(array, resposta, 3);

    int array2[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int resposta2[] = {1, 2, 3, 4, 5, 6, 7, 8};
    heap_sort(array2, 8);
    imprimir_vetor(array2, 8);
    teste_heap(array2, resposta2, 8);

    int array3[] = {1, 2, 3, 4, 5};
    int resposta3[] = {1, 2, 3, 4, 5};
    heap_sort(array3, 5);
    imprimir_vetor(array3, 5);
    teste_heap(array3, resposta3, 5);

    int array4[] = {5, 4, 1, 2, 7, 10, 0};
    int resposta4[] = {0, 1, 2, 4, 5, 7, 10};
    heap_sort(array4, 7);
    imprimir_vetor(array4, 7);
    teste_heap(array4, resposta4, 7);
}

int main() {
    teste_pai();
    teste_filho_esq();
    teste_filho_dir();
    teste_constroi_heap();
    teste_desce();    
    teste_sobe();
    teste_extrai_max();
    teste_insere_elemento();
    teste_altera_prioridade();
    teste_heap_sort();

    return EXIT_SUCCESS;
}                   
