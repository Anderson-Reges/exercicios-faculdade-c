#include <stdio.h>

void towerMoviment(int number)
{
  if (number > 0)
  {
    printf("Direita\n");
    towerMoviment(number - 1);
  };
}

void queenMoviment(int number)
{
  if (number > 0)
  {
    printf("Cima\n");
    queenMoviment(number - 1);
  }
}

void bishopMovimentRecursive(int vertical, int horizontal)
{
  if (vertical > 0)
  {
    for (int i = 0; i < horizontal; i++)
    {
      printf("Cima, Direita\n");
    }
    
    bishopMovimentRecursive(vertical - 1, horizontal);
  }
}

void horseMoviment(int moves)
{
  for (int i = 0; i < moves; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (j < 2)
      {
        printf("Cima\n");
      }
      else
      {
        printf("Esquerda\n");
      }
    }
  }
}

int main(void)
{
  // Movimentos das peças
  int bishop_moviment_number_vertical = 3;
  int bishop_moviment_number_horizontal = 2;
  int tower_moviment_number = 5;
  int queen_moviment_number = 8;
  int horse_moviment_number = 1;
  int while_count = 0;
  int do_while_count = 0;

  // Torre
  printf("Torre:\n");
  towerMoviment(tower_moviment_number);

  // Bispo
  printf("\nBispo:\n");
  bishopMovimentRecursive(bishop_moviment_number_vertical, bishop_moviment_number_horizontal);

  // Rainha
  printf("\nRainha:\n");
  queenMoviment(queen_moviment_number);

  // Cavalo
  printf("\nCavalo:\n");
  horseMoviment(horse_moviment_number);

  return 0;
}