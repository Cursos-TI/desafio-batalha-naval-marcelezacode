#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAM_TAB 10
#define TAM_HAB 5
#define NAVIO 3

// Inicializa o tabuleiro com água (0)
void inicializarTabuleiro(int tab[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++)
        for (int j = 0; j < TAM_TAB; j++)
            tab[i][j] = 0;
}

// Exibe o tabuleiro com cabeçalho e legenda (usando números 0, 3 e 5)
void exibirTabuleiro(int tab[TAM_TAB][TAM_TAB]) {
    printf("\n===== BATALHA NAVAL =====\n\n");
    printf("    ");
    for (int j = 0; j < TAM_TAB; j++)
        printf(" %c ", 'A' + j);
    printf("\n");

    for (int i = 0; i < TAM_TAB; i++) {
        printf("%2d  ", i);
        for (int j = 0; j < TAM_TAB; j++) {
            printf(" %d ", tab[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = Água | 3 = Navio | 5 = Área afetada pela habilidade\n");
}

// Posiciona um navio simples
void posicionarNavio(int tab[TAM_TAB][TAM_TAB], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') {
        for (int j = 0; j < NAVIO; j++)
            tab[linha][coluna + j] = 3;
    } else if (orientacao == 'V') {
        for (int i = 0; i < NAVIO; i++)
            tab[linha + i][coluna] = 3;
    }
}

// Aplica matriz de habilidade (5) ao tabuleiro, respeitando limites
void aplicarHabilidade(int tab[TAM_TAB][TAM_TAB], int hab[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int offset = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (hab[i][j] == 1) {
                int linhaTab = origemLinha - offset + i;
                int colunaTab = origemColuna - offset + j;
                if (linhaTab >= 0 && linhaTab < TAM_TAB && colunaTab >= 0 && colunaTab < TAM_TAB) {
                    if (tab[linhaTab][colunaTab] == 0)
                        tab[linhaTab][colunaTab] = 5;
                }
            }
        }
    }
}

// Gera matriz de habilidade tipo CONE (↧)
void criarCone(int hab[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB / 2 - i) && j <= (TAM_HAB / 2 + i))
                hab[i][j] = 1;
            else
                hab[i][j] = 0;
        }
    }
}

// Gera matriz de habilidade tipo CRUZ (+)
void criarCruz(int hab[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            hab[i][j] = (i == centro || j == centro) ? 1 : 0;
        }
    }
}

// Gera matriz de habilidade tipo OCTAEDRO (losango)
void criarOctaedro(int hab[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                hab[i][j] = 1;
            else
                hab[i][j] = 0;
        }
    }
}

// Exibe uma matriz de habilidade isolada (para exemplo visual)
void exibirHabilidade(const char *nome, int hab[TAM_HAB][TAM_HAB]) {
    printf("\n===== HABILIDADE: %s =====\n\n", nome);
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            printf(" %d ", hab[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB];
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    inicializarTabuleiro(tabuleiro);

    // Criar matrizes de habilidade
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Exibir exemplos isolados de habilidades
    exibirHabilidade("CONE", cone);
    exibirHabilidade("CRUZ", cruz);
    exibirHabilidade("OCTAEDRO", octaedro);

    // Posicionar navios
    posicionarNavio(tabuleiro, 2, 4, 'H');
    posicionarNavio(tabuleiro, 6, 2, 'V');

    // Aplicar habilidades no tabuleiro principal
    aplicarHabilidade(tabuleiro, cone, 2, 2);      // cone no topo esquerdo
    aplicarHabilidade(tabuleiro, cruz, 6, 6);      // cruz no meio
    aplicarHabilidade(tabuleiro, octaedro, 4, 8);  // octaedro à direita

    // Exibir tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}