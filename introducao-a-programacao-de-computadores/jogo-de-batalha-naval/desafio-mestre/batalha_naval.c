#include <stdio.h>
#include <stdlib.h>

// Função para sobrepor uma matriz de habilidade no tabuleiro
void apply_skill(int board[10][10], int skill[5][5], int origin_row, int origin_col) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      int board_row = origin_row + i - 2; // Ajustar para centralizar a matriz
      int board_col = origin_col + j - 2;
      if (board_row >= 0 && board_row < 10 && board_col >= 0 && board_col < 10 && skill[i][j] == 1) {
        board[board_row][board_col] = 5; // Marcar área afetada
      }
    }
  }
}

int main(void)
{
  int board[10][10] = {0}; // Tabuleiro inicializado com água (0)
  int ship1[3] = {3, 3, 3}; // Exemplo de navio
  int ship1_start_row = 2, ship1_start_col = 2;

  // Posicionar o navio no tabuleiro
  for (int i = 0; i < 3; i++) {
    board[ship1_start_row][ship1_start_col + i] = 3;
  }

  // Matriz de habilidade Cone
  int cone[5][5] = {
      {0, 0, 1, 0, 0},
      {0, 1, 1, 1, 0},
      {1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}};

  // Matriz de habilidade Cruz
  int cross[5][5] = {
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {1, 1, 1, 1, 1},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0}};

  // Matriz de habilidade Octaedro
  int octahedron[5][5] = {
      {0, 0, 1, 0, 0},
      {0, 1, 1, 1, 0},
      {1, 1, 1, 1, 1},
      {0, 1, 1, 1, 0},
      {0, 0, 1, 0, 0}};

  // Aplicar habilidades no tabuleiro
  apply_skill(board, cone, 4, 4);       // Cone com origem em (4, 4)
  apply_skill(board, cross, 6, 4);     // Cruz com origem em (6, 6)
  apply_skill(board, octahedron, 6, 8); // Octaedro com origem em (8, 8)

  // Exibir o tabuleiro
  printf("Tabuleiro:\n");
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (board[i][j] == 0) {
        printf(". ");
      } else if (board[i][j] == 3) {
        printf("X ");
      } else if (board[i][j] == 5) {
        printf("O ");
      }
    }
    printf("\n");
  }

  return 0;
}