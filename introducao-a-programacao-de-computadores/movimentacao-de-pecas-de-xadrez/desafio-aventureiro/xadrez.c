#include <stdio.h>

int main(void)
{
  // Movimentos das peças
  int bishop_moviment_number = 5;
  int tower_moviment_number = 5;
  int queen_moviment_number = 8;
  int horse_moviment_number = 1;
  int while_count = 0;
  int do_while_count = 0;

  // Torre
  printf("Torre:\n");
  for (int i = 0; i < tower_moviment_number; i++)
  {
    printf("Direita\n");
  }

  // Bispo
  printf("\nBispo:\n");
  while (while_count < bishop_moviment_number)
  {
    printf("Cima, Direita\n");
    while_count++;
  }

  // Rainha
  printf("\nRainha:\n");
  do
  {
    printf("Cima\n");
    do_while_count++;
  } while (do_while_count < queen_moviment_number);

  // Cavalo
  printf("\nCavalo:\n");
  for (int i = 0; i < horse_moviment_number; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      printf("Cima\n");
    }
    printf("Esquerda\n");
  }

  return 0;
}