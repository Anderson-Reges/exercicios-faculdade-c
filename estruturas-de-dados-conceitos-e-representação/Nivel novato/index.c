#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura para representar um território */
struct Territorio
{
  char nome[100];
  char cor[10];
  int tropas;
};

int main(void)
{
  /* Define o número máximo de territórios */
  int MAX_TERRITORIOS = 5;
  /* Limita o número de territórios a serem cadastrados */
  int num_territorios = 0;
  /* Cria um array de estruturas para armazenar os territórios */
  struct Territorio territorios[MAX_TERRITORIOS];

  /* Utiliza um Do-While para permitir o cadastro de múltiplos territórios */
  do
  {
    printf("Cadastre seu primeiro Territorio(%d): \n", num_territorios + 1);
    /* Solicitar informações do território */
    printf("Digite o nome do territorio: \n");

    /* Lê o nome do território, limpando o buffer */
    fgets(territorios[num_territorios].nome, sizeof(territorios[num_territorios].nome), stdin);
    territorios[num_territorios].nome[strcspn(territorios[num_territorios].nome, "\n")] = '\0';

    /* Solicitar a cor do território, limpando o buffer */
    printf("Digite a cor do territorio: \n");
    fgets(territorios[num_territorios].cor, sizeof(territorios[num_territorios].cor), stdin);
    territorios[num_territorios].cor[strcspn(territorios[num_territorios].cor, "\n")] = '\0';

    /* Solicitar o número de tropas do território, limpando o buffer */
    printf("Digite o numero de tropas do territorio: \n");
    scanf("%d", &territorios[num_territorios].tropas);
    getchar();

    /* Lê o número de tropas do território e adiciona ao total */
    num_territorios++;

  } while (num_territorios < MAX_TERRITORIOS);

  /* Exibe os territórios cadastrados */
  printf("\nTerritorios cadastrados:\n");
  for (int i = 0; i < num_territorios; i++)
  {
    printf("---------------------\n");
    printf("Territorio %d:\n", i + 1);
    printf("Nome: %s\n", territorios[i].nome);
    printf("Cor: %s\n", territorios[i].cor);
    printf("Tropas: %d\n\n", territorios[i].tropas);
  }

  return 0;
}