#include <stdio.h>
#include <stdbool.h>

#define TAM 10
#define NAVIO 3

// Inicializa o tabuleiro com água (0)
void inicializar(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = 0;
}

// Exibe o tabuleiro com cabeçalho A–J
void exibir(int tab[TAM][TAM]) {
    printf("\n===== BATALHA NAVAL =====\n\n");
    printf("    ");

    for (int j = 0; j < TAM; j++)
        printf(" %c ", 'A' + j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d  ", i);
        for (int j = 0; j < TAM; j++)
            printf(" %d ", tab[i][j]);
        printf("\n");
    }
    printf("\nLegenda: 0 = água | 3 = navio\n\n");
}

// Verifica se pode colocar navio horizontal, vertical ou diagonal
bool podeColocar(int tab[TAM][TAM], int linha, int coluna, char orient) {
    int i, j;

    switch (orient) {

        case 'H': // Horizontal →
            if (coluna + NAVIO > TAM) return false;
            for (j = 0; j < NAVIO; j++)
                if (tab[linha][coluna + j] != 0) return false;
            break;

        case 'V': // Vertical ↓
            if (linha + NAVIO > TAM) return false;
            for (i = 0; i < NAVIO; i++)
                if (tab[linha + i][coluna] != 0) return false;
            break;

        case 'D': // Diagonal ↘  (linha++, coluna++)
            if (linha + NAVIO > TAM || coluna + NAVIO > TAM) return false;
            for (i = 0; i < NAVIO; i++)
                if (tab[linha + i][coluna + i] != 0) return false;
            break;

        case 'E': // Diagonal ↙  (linha++, coluna--)
            if (linha + NAVIO > TAM || coluna - (NAVIO - 1) < 0) return false;
            for (i = 0; i < NAVIO; i++)
                if (tab[linha + i][coluna - i] != 0) return false;
            break;

        default:
            return false;
    }

    return true;
}

// Posiciona navio no tabuleiro
void posicionar(int tab[TAM][TAM], int linha, int coluna, char orient) {
    int i;

    switch (orient) {

        case 'H': // →
            for (i = 0; i < NAVIO; i++)
                tab[linha][coluna + i] = 3;
            break;

        case 'V': // ↓
            for (i = 0; i < NAVIO; i++)
                tab[linha + i][coluna] = 3;
            break;

        case 'D': // ↘
            for (i = 0; i < NAVIO; i++)
                tab[linha + i][coluna + i] = 3;
            break;

        case 'E': // ↙
            for (i = 0; i < NAVIO; i++)
                tab[linha + i][coluna - i] = 3;
            break;
    }
}

int main() {
    int tab[TAM][TAM];

    inicializar(tab);

    // NAVIOS (4 navios total)
    // Você pode trocar essas coordenadas se quiser testar posições diferentes:
    int l1 = 2, c1 = 4;  // Horizontal
    int l2 = 5, c2 = 1;  // Vertical
    int l3 = 1, c3 = 1;  // Diagonal ↘
    int l4 = 1, c4 = 8;  // Diagonal ↙

    // Posicionar navio 1 (horizontal)
    if (podeColocar(tab, l1, c1, 'H'))
        posicionar(tab, l1, c1, 'H');

    // Posicionar navio 2 (vertical)
    if (podeColocar(tab, l2, c2, 'V'))
        posicionar(tab, l2, c2, 'V');

    // Posicionar navio 3 (diagonal principal ↘)
    if (podeColocar(tab, l3, c3, 'D'))
        posicionar(tab, l3, c3, 'D');

    // Posicionar navio 4 (diagonal secundária ↙)
    if (podeColocar(tab, l4, c4, 'E'))
        posicionar(tab, l4, c4, 'E');

    // Exibir tabuleiro
    exibir(tab);

    return 0;
}
