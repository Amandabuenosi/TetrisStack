#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5  

// Representa uma peça do jogo
typedef struct {
    char nome;  // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;     // Identificador único da peça
} Peca;

// Representa a fila circular de peças
typedef struct {
    Peca pecas[TAM_FILA];
    int frente;  // Índice da primeira peça
    int tras;    // Índice da última peça
    int qtd;     // Quantidade de peças atuais
} Fila;


// Inicializa a fila vazia
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->qtd == TAM_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->qtd == 0;
}

// Gera automaticamente uma nova peça
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4]; // Tipo aleatório
    nova.id = id;                  
    return nova;
}

// nova peça ao final da fila (enqueue)
void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\nFila cheia! Nao e possivel adicionar nova peca.\n");
        return;
    }
    f->tras = (f->tras + 1) % TAM_FILA;
    f->pecas[f->tras] = p;
    f->qtd++;
    printf("Peca [%c %d] adicionada ao final da fila!\n", p.nome, p.id);
}

// Remove da frente da fila (dequeue)
void desenfileirar(Fila *f) {
    if (filaVazia(f)) {
        printf("\nFila vazia! Nenhuma peca para jogar.\n");
        return;
    }
    Peca removida = f->pecas[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
    printf("\nPeca [%c %d] jogada!\n", removida.nome, removida.id);
}

// estado atual da fila
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("\nFila vazia!\n");
        return;
    }

    printf("\n=== FILA DE PECAS FUTURAS ===\n");
    for (int i = 0; i < f->qtd; i++) {
        int idx = (f->frente + i) % TAM_FILA;
        printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
    }
    printf("\n=============================\n");
}


int main() {
    Fila fila;
    int opcao, idGerado = 0;
    srand(time(NULL));

    inicializarFila(&fila);

    // fila com 5 peças aleatórias
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(idGerado++));
    }

        // MENU
        do {
        printf("\n===== MENU TETRIS STACK =====\n");
        printf("1 - Visualizar fila de pecas\n");
        printf("2 - Jogar uma peca (remover da frente)\n");
        printf("3 - Adicionar nova peca (inserir no final)\n");
        printf("0 - Sair\n");
        printf("=============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                exibirFila(&fila);
                break;
            case 2:
                desenfileirar(&fila);
                break;
            case 3:
                enfileirar(&fila, gerarPeca(idGerado++));
                break;
            case 0:
                printf("\nEncerrando o jogo... Ate a proxima!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
