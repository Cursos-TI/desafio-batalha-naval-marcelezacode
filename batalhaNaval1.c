#include <stdio.h>
#include <stdbool.h>

#define TAMANHO 10
#define NAVIO 3

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
for (int i = 0; i < TAMANHO; i++) {
for (int j = 0; j < TAMANHO; j++) {
           tabuleiro[i][j] = 0;
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {

printf("\n===  Batalha Naval ===\n\n");

    // Cabeçalho (colunas A..J)
printf("   ");
for (int j = 0; j < TAMANHO; j++) {
printf(" %c", 'A' + j);
    }
printf("\n");

    // Linhas 0..9
for (int i = 0; i < TAMANHO; i++) {
printf("%2d ", i);
for (int j = 0; j < TAMANHO; j++) {
printf(" %d", tabuleiro[i][j]);
        }
printf("\n");
    }

printf("\nLegenda: 0 = Água | 3 = Navio\n\n");
}

bool podeColocarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {

if (orientacao == 'H' || orientacao == 'h') {

if (coluna + NAVIO > TAMANHO)
    return false;

for (int j = 0; j < NAVIO; j++) {
if (tabuleiro[linha][coluna + j] != 0)
return false;
        }

 } else if (orientacao == 'V' || orientacao == 'v') {
if (linha + NAVIO > TAMANHO)
return false;

for (int i = 0; i < NAVIO; i++) {
if (tabuleiro[linha + i][coluna] != 0)
return false;
    }

} else {
 return false; 
    }

    return true;
}

void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {

if (orientacao == 'H' || orientacao == 'h') {
for (int j = 0; j < NAVIO; j++)
           tabuleiro[linha][coluna + j] = 3;

 } else {
for (int i = 0; i < NAVIO; i++)
            tabuleiro[linha + i][coluna] = 3;
    }
}

int main() {

int tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);

    // TESTE 1 – Navio Horizontal
 int l1 = 2, c1 = 4;

if (podeColocarNavio(tabuleiro, l1, c1, 'H')) {
        posicionarNavio(tabuleiro, l1, c1, 'H');
} else {
printf("Erro ao posicionar navio horizontal!\n");
}

    // TESTE 2 – Navio Vertical
int l2 = 5, c2 = 7;

if (podeColocarNavio(tabuleiro, l2, c2, 'V')) {
        posicionarNavio(tabuleiro, l2, c2, 'V');
} else {
printf("Erro ao posicionar navio vertical!\n");
}

exibirTabuleiro(tabuleiro);

    return 0;
}