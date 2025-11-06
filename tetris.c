#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// ======================================
// ESTRUTURA DAS PEÇAS
// ======================================
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único
} Peca;

// ======================================
// ESTRUTURAS DE DADOS
// ======================================

// Fila circular de peças futuras
typedef struct {
    Peca pecas[TAM_FILA];
    int frente;
    int tras;
    int qtd;
} Fila;

// Pilha de peças reservadas
typedef struct {
    Peca pecas[TAM_PILHA];
    int topo;
} Pilha;

// ======================================
// FUNÇÕES DE CONTROLE DE FILA
// ======================================
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
}

int filaCheia(Fila *f) {
    return f->qtd == TAM_FILA;
}

int filaVazia(Fila *f) {
    return f->qtd == 0;
}

void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->tras = (f->tras + 1) % TAM_FILA;
    f->pecas[f->tras] = p;
    f->qtd++;
}

Peca desenfileirar(Fila *f) {
    Peca p = {'-', -1};
    if (filaVazia(f)) return p;
    p = f->pecas[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
    return p;
}

// ======================================
// FUNÇÕES DE CONTROLE DE PILHA
// ======================================
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, Peca novo) {
    if (pilhaCheia(p)) {
        printf("\n❌ Pilha cheia! Nao e possivel reservar mais pecas.\n");
        return;
    }
    p->topo++;
    p->pecas[p->topo] = novo;
    printf("\n📦 Peca [%c %d] adicionada à pilha de reserva.\n", novo.nome, novo.id);
}

Peca desempilhar(Pilha *p) {
    Peca removida = {'-', -1};
    if (pilhaVazia(p)) {
        printf("\n❌ Pilha vazia! Nenhuma peca para usar.\n");
        return removida;
    }
    removida = p->pecas[p->topo];
    p->topo--;
    printf("\n🎮 Peca [%c %d] usada da pilha.\n", removida.nome, removida.id);
    return removida;
}

// ======================================
// FUNÇÃO DE GERAÇÃO DE PEÇAS AUTOMÁTICA
// ======================================
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// ======================================
// FUNÇÃO DE EXIBIÇÃO DO ESTADO
// ======================================
void exibirEstado(Fila *f, Pilha *p) {
    printf("\n=== ESTADO ATUAL ===\n");

    // Exibe fila
    printf("Fila de pecas:\t");
    if (filaVazia(f)) printf("(vazia)");
    else {
        for (int i = 0; i < f->qtd; i++) {
            int idx = (f->frente + i) % TAM_FILA;
            printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
        }
    }

    // Exibe pilha
    printf("\nPilha de reserva (Topo -> base): ");
    if (pilhaVazia(p)) printf("(vazia)");
    else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->pecas[i].nome, p->pecas[i].id);
        }
    }
    printf("\n====================\n");
}

// ======================================
// TROCAS ENTRE FILA E PILHA
// ======================================

// Troca a peça da frente da fila com o topo da pilha
void trocarTopo(Fila *f, Pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("\n❌ Impossível trocar! Fila ou pilha vazia.\n");
        return;
    }
    int idxFrente = f->frente;
    Peca temp = f->pecas[idxFrente];
    f->pecas[idxFrente] = p->pecas[p->topo];
    p->pecas[p->topo] = temp;
    printf("\n🔄 Troca realizada entre topo da pilha e frente da fila!\n");
}

// Troca múltipla: 3 primeiros da fila ↔ 3 da pilha
void trocaMultipla(Fila *f, Pilha *p) {
    if (f->qtd < 3 || p->topo < 2) {
        printf("\n❌ Troca múltipla indisponível (menos de 3 peças em uma das estruturas).\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idx = (f->frente + i) % TAM_FILA;
        Peca temp = f->pecas[idx];
        f->pecas[idx] = p->pecas[p->topo - i];
        p->pecas[p->topo - i] = temp;
    }

    printf("\n🔁 Troca múltipla realizada entre as 3 primeiras da fila e as 3 da pilha!\n");
}

// ======================================
// FUNÇÃO PRINCIPAL
// ======================================
int main() {
    Fila fila;
    Pilha pilha;
    int opcao, idGerado = 0;
    srand(time(NULL));

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(idGerado++));
    }

    do {
        printf("\n===== MENU TETRIS STACK =====\n");
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para pilha de reserva\n");
        printf("3 - Usar peca da pilha de reserva\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Troca multipla (3 primeiras da fila ↔ 3 da pilha)\n");
        printf("6 - Visualizar estado atual\n");
        printf("0 - Sair\n");
        printf("=============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                // Jogar peça (remove da fila e gera nova)
                Peca jogada = desenfileirar(&fila);
                if (jogada.id != -1) {
                    printf("\n🎮 Peca [%c %d] jogada do campo!\n", jogada.nome, jogada.id);
                    if (!filaCheia(&fila)) {
                        enfileirar(&fila, gerarPeca(idGerado++));
                    }
                }
                break;
            }
            case 2: {
                // Reservar peça (fila → pilha)
                if (pilhaCheia(&pilha)) {
                    printf("\n❌ Pilha cheia! Nao e possivel reservar mais pecas.\n");
                } else {
                    Peca reservada = desenfileirar(&fila);
                    if (reservada.id != -1) {
                        empilhar(&pilha, reservada);
                        if (!filaCheia(&fila)) {
                            enfileirar(&fila, gerarPeca(idGerado++));
                        }
                    }
                }
                break;
            }
            case 3:
                desempilhar(&pilha);
                break;
            case 4:
                trocarTopo(&fila, &pilha);
                break;
            case 5:
                trocaMultipla(&fila, &pilha);
                break;
            case 6:
                exibirEstado(&fila, &pilha);
                break;
            case 0:
                printf("\n🏁 Encerrando o jogo... Ate a proxima!\n");
                break;
            default:
                printf("\n❌ Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
