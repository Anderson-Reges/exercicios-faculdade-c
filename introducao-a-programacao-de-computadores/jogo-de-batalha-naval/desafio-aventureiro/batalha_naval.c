#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int *board[10][10] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  int ship1[3], ship2[3], ship3[3], ship4[3] = {3, 3, 3};

  int ship1_start_row, ship1_start_col;
  int ship2_start_row, ship2_start_col;
  int ship3_start_row, ship3_start_col;
  int ship4_start_row, ship4_start_col;

  // Entrada das coordenadas para o navio 1
  printf("Digite as coordenadas iniciais do navio 1 (linha e coluna): ");
  scanf("%d %d", &ship1_start_row, &ship1_start_col);

  // Validar a posição do navio 1
  if (ship1_start_row < 0 || ship1_start_row + 3 > 10 || ship1_start_col < 0 || ship1_start_col + 3 > 10)
  {
    printf("Erro: As coordenadas ou o tamanho do navio 1 são inválidos.\n");
    return 1;
  }

  // Entrada das coordenadas para o navio 2
  printf("Digite as coordenadas iniciais do navio 2 (linha e coluna): ");
  scanf("%d %d", &ship2_start_row, &ship2_start_col);

  // Validar a posição do navio 2
  if (ship2_start_row < 0 || ship2_start_row + 3 > 10 || ship2_start_col < 0 || ship2_start_col >= 10)
  {
    printf("Erro: As coordenadas ou o tamanho do navio 2 são inválidos.\n");
    return 1;
  }

  // Entrada das coordenadas para o navio 3
  printf("Digite as coordenadas iniciais do navio 3 (linha e coluna): ");
  scanf("%d %d", &ship3_start_row, &ship3_start_col);

  // Validar a posição do navio 3 para a diagonal esquerda
  if (ship3_start_row < 0 || ship3_start_row + 3 > 10 || ship3_start_col - 2 < 0 || ship3_start_col >= 10)
  {
    printf("Erro: As coordenadas ou o tamanho do navio 3 são inválidos.\n");
    return 1;
  }

  // Entrada das coordenadas para o navio 4 (diagonal para a direita)
  printf("Digite as coordenadas iniciais do navio 4 (linha e coluna): ");
  scanf("%d %d", &ship4_start_row, &ship4_start_col);

  // Validar a posição do navio 4 para a diagonal direita
  if (ship4_start_row < 0 || ship4_start_row + 3 > 10 || ship4_start_col < 0 || ship4_start_col + 3 > 10)
  {
    printf("Erro: As coordenadas ou o tamanho do navio 4 são inválidos.\n");
    return 1;
  }

  // Verificar sobreposição dos navios
  for (int i = 0; i < 3; i++)
  {
    if (board[ship1_start_row][ship1_start_col + i] != NULL ||
        board[ship2_start_row + i][ship2_start_col] != NULL ||
        board[ship3_start_row + i][ship3_start_col - i] != NULL ||
        board[ship4_start_row + i][ship4_start_col + i] != NULL)
    {
      printf("Erro: Há sobreposição de navios no tabuleiro.\n");
      return 1;
    }
  }

  // Posicionar os navios horizontal e vertical no tabuleiro
  for (int i = 0; i < 3; i++)
  {
    board[ship1_start_row][ship1_start_col + i] = &ship1[i];
    board[ship2_start_row + i][ship2_start_col] = &ship2[i];
    board[ship3_start_row + i][ship3_start_col - i] = &ship3[i];
    board[ship4_start_row + i][ship4_start_col + i] = &ship4[i];
  }

  // Exibir o tabuleiro
  printf("Tabuleiro:\n");
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      if (board[i][j] != NULL)
      {
        printf("X ");
      }
      else
      {
        printf(". ");
      }
    }
    printf("\n");
  }

  return 0;
}