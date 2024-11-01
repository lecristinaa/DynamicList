#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **dados;      // Ponteiro genérico para os elementos da fila
    int inicio;        // Índice do primeiro elemento
    int fim;           // Índice do último elemento
    int tamanho;       // Capacidade atual da fila
    int capacidade;    // Capacidade total da fila
} Fila;

// Função para criar a fila
Fila* criarFila(int capacidadeInicial) {
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    if (fila == NULL) return NULL;  // Verifica se a alocação foi bem-sucedida

    fila->dados = (void **) malloc(sizeof(void*) * capacidadeInicial);
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
    fila->capacidade = capacidadeInicial;

    return fila;
}

// Função para limpar e liberar a fila
void limparFila(Fila *fila) {
    if (fila != NULL) {
        free(fila->dados);  // Libera a memória alocada para os dados
        free(fila);         // Libera a memória da estrutura da fila
    }
}

// Função para dobrar a capacidade da fila
void dobrarCapacidade(Fila *fila) {
    int novaCapacidade = fila->capacidade * 2;
    void **novosDados = (void **) malloc(sizeof(void*) * novaCapacidade);

    for (int i = 0; i < fila->tamanho; i++) {
        novosDados[i] = fila->dados[(fila->inicio + i) % fila->capacidade];
    }

    free(fila->dados);
    fila->dados = novosDados;
    fila->inicio = 0;
    fila->fim = fila->tamanho - 1;
    fila->capacidade = novaCapacidade;
}

// Função para inserir um elemento na fila
void inserirNaFila(Fila *fila, void *item) {
    if (fila->tamanho == fila->capacidade) {
        dobrarCapacidade(fila);
    }

    fila->fim = (fila->fim + 1) % fila->capacidade;
    fila->dados[fila->fim] = item;
    fila->tamanho++;
}
    
// Função para remover um elemento da fila
void* removerDaFila(Fila *fila) {
    if (fila->tamanho == 0) return NULL;  // Fila vazia

    void *item = fila->dados[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->tamanho--;

    return item;
}


// Função principal
int main(){
    Fila *fila = criarFila(2);

    int item1=15, item2=27, item3=39, item4=43;
    inserirNaFila(fila, &item1);
    inserirNaFila(fila, &item2);

    printf("Capacidade atual da fila: %d\n", fila->capacidade); // Deve printar 2
    
    inserirNaFila(fila, &item3);
    inserirNaFila(fila, &item4);

    printf("\nCapacidade atual da fila: %d\n", fila->capacidade); // Deve printar 4

    // Exibe os elementos da fila
    printf("\nElementos da fila:\n");
    for (int i = 0; i < fila->tamanho; i++) {
        int index = (fila->inicio + i) % fila->capacidade;
        printf("%d ", *(int*)fila->dados[index]);
    }
    printf("\n\n");

    // Removendo os elementos da fila
    printf("Removendo: %d \n", *(int*)(removerDaFila(fila)));
    printf("Removendo: %d \n", *(int*)(removerDaFila(fila)));
    printf("Removendo: %d \n", *(int*)(removerDaFila(fila)));
    printf("Removendo: %d \n", *(int*)(removerDaFila(fila)));

    limparFila(fila);
    return 0;
}
