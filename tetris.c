#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5 


// ESTRUTURA DE DADOS

typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    
} Peca;

typedef struct {
    Peca pecas[TAM_FILA];
    int frente;   // Índice da primeira peça
    int tras;     // Índice da última peça
    int qtd;      // Quantidade de elementos na fila
} Fila;


// FUNÇÕES DA FILA

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
}

// Verifica se está cheia
int filaCheia(Fila *f) {
    return f->qtd == TAM_FILA;
}

// Verifica se está vazia
int filaVazia(Fila *f) {
    return f->qtd == 0;
}

// Gera automaticamente uma nova peça aleatória
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4]; // Escolhe um tipo aleatório
    nova.id = id;
    return nova;
}

// Insere nova peça no fim da fila (enqueue)
void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Nao e possivel adicionar nova peca.\n");
        return;
    }
    f->tras = (f->tras + 1) % TAM_FILA;
    f->pecas[f->tras] = p;
    f->qtd++;
    printf("Peca [%c %d] adicionada ao final da fila!\n", p.nome, p.id);
}

// Remove peça da frente da fila (dequeue)
void desenfileirar(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nenhuma peca para jogar.\n");
        return;
    }
    Peca removida = f->pecas[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
    printf("Peca [%c %d] jogada!\n", removida.nome, removida.id);
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("\nFila vazia!\n");
        return;
    }

    printf("\n=== FILA DE PECAS FUTURAS ===\n");
    int i, idx;
    for (i = 0; i < f->qtd; i++) {
        idx = (f->frente + i) % TAM_FILA;
        printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
    }
    printf("\n=============================\n");
}


// PROGRAMA PRINCIPAL

int main() {
    Fila fila;
    int opcao, idGerado = 0;

    srand(time(NULL)); // Garante aleatoriedade
    inicializarFila(&fila);

    // Inicializa a fila com 5 peças aleatórias
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(idGerado++));
    };
};
