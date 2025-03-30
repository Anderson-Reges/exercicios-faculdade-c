#include <stdio.h>

int main(void)
{
  int bishop_moviment_number = 5;
  int tower_moviment_number = 5;
  int queen_moviment_number = 8;
  int while_count = 0;
  int do_while_count = 0;

  printf("Torre:\n");
  for (int i = 0; i < tower_moviment_number; i++)
  {
    printf("Direita\n");
  }

  printf("\nBispo:\n");
  while (while_count < bishop_moviment_number)
  {
    printf("Cima, Direita\n");
    while_count++;
  }

  printf("\nRainha:\n");
  do
  {
    printf("Cima\n");
    do_while_count++;
  } while (do_while_count < queen_moviment_number);

  return 0;
}