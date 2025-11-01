#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Estrutura para representar um território */
typedef struct
{
  char nome[30];
  char cor[10];
  int tropas;
} Territorio;

/* util: limpar resto da linha */
static void limpar_linha(void)
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }
}

/* util: tirar '\n' do final */
static void tira_newline(char *s)
{
  s[strcspn(s, "\n")] = '\0';
}

/* D6: 1..6 */
static int rolar_d6(void)
{
  return 1 + rand() % 6;
}

/* Verifica se existe ao menos uma batalha possivel:
   dois territorios de cores diferentes e com tropas > 0 */
static int existe_batalha_possivel(const Territorio *v, int n)
{
  for (int i = 0; i < n; i++)
  {
    if (v[i].tropas <= 0)
      continue;
    for (int j = 0; j < n; j++)
    {
      if (i == j || v[j].tropas <= 0)
        continue;
      if (strcmp(v[i].cor, v[j].cor) != 0)
        return 1;
    }
  }
  return 0;
}

/* Pergunta ao usuario se deseja continuar batalhando */
static int perguntar_continuar(void)
{
  char resp[8];
  printf("\nDeseja realizar outra batalha? (s/n): ");
  if (!fgets(resp, sizeof(resp), stdin))
    return 0;
  return (resp[0] == 's' || resp[0] == 'S');
}

/* Regra mantida:
   - Quem perde no round perde metade das tropas atuais (min 1 se houver tropas).
   - Se o defensor zera/negativa, o atacante conquista e move metade das próprias tropas. */
void atacar(Territorio *atacante, Territorio *defensor, int (*rand_func)(void))
{
  while (atacante->tropas > 0 && defensor->tropas > 0)
  {
    int ataque = rand_func();
    int defesa = rand_func();

    printf("%s ataca %s!\n", atacante->nome, defensor->nome);
    printf("Dado do atacante: %d vs Dado do defensor: %d\n", ataque, defesa);

    if (ataque > defesa)
    {
      int perdas_def = defensor->tropas / 2;
      if (perdas_def < 1 && defensor->tropas > 0)
        perdas_def = 1;
      defensor->tropas -= perdas_def;
      printf("%s vence! %s perde %d tropas.\n", atacante->nome, defensor->nome, perdas_def);

      if (defensor->tropas <= 0)
      {
        int transfer = atacante->tropas / 2;
        if (transfer < 1 && atacante->tropas > 0)
          transfer = 1;
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = transfer;
        atacante->tropas -= transfer;
        printf("%s foi derrotado! %s conquistou o territorio e moveu %d tropas.\n",
               defensor->nome, atacante->nome, transfer);
        break;
      }
    }
    else
    {
      int perdas_atk = atacante->tropas / 2;
      if (perdas_atk < 1 && atacante->tropas > 0)
        perdas_atk = 1;
      atacante->tropas -= perdas_atk;
      printf("%s defende com sucesso! %s perde %d tropas.\n", defensor->nome, atacante->nome, perdas_atk);

      if (atacante->tropas <= 0)
      {
        printf("%s ficou sem tropas para continuar o ataque.\n", atacante->nome);
        printf("%s defendeu o territorio com sucesso!\n", defensor->nome);
        break;
      }
    }

    printf("Tropas restantes - %s: %d, %s: %d\n",
           atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
  }
}

int main(void)
{
  srand((unsigned)time(NULL));

  int MAX_TERRITORIOS;

  /* Define a quantidade máxima de territórios */
  printf("Defina quantidades de territorios para o mapa: ");
  if (scanf("%d", &MAX_TERRITORIOS) != 1 || MAX_TERRITORIOS <= 0)
  {
    fprintf(stderr, "Quantidade invalida.\n");
    return 1;
  }
  limpar_linha();

  /* Alocação da memória para os territórios */
  Territorio *territorios = (Territorio *)malloc(MAX_TERRITORIOS * sizeof(Territorio));
  if (!territorios)
  {
    perror("Falha ao alocar memoria");
    return 1;
  }

  /* Cadastro dos territórios */
  for (int i = 0; i < MAX_TERRITORIOS; i++)
  {
    printf("Cadastre o Territorio(%d): \n", i + 1);

    printf("Digite o nome do territorio:\n");
    if (!fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin))
    {
      free(territorios);
      return 1;
    }
    tira_newline(territorios[i].nome);

    printf("Digite a cor do territorio:\n");
    if (!fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin))
    {
      free(territorios);
      return 1;
    }
    tira_newline(territorios[i].cor);

    printf("Digite o numero de tropas do territorio:\n");
    while (scanf("%d", &territorios[i].tropas) != 1 || territorios[i].tropas < 0)
    {
      printf("Valor invalido. Digite um inteiro >= 0: ");
      limpar_linha();
    }
    limpar_linha();
  }

  /* Seleção do atacante */
  while (1)
  {
    if (!existe_batalha_possivel(territorios, MAX_TERRITORIOS))
    {
      printf("\nNao ha mais batalhas possiveis (faltam tropas ou todos sao da mesma cor).\n");
      break;
    }

    int atacante_idx_1;
    while (1)
    {
      printf("\nSelecione um territorio para atacar (ATACANTE): \n");
      for (int i = 0; i < MAX_TERRITORIOS; i++)
      {
        printf("%d - %s (Cor: %s, Tropas: %d)\n", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
      }
      if (scanf("%d", &atacante_idx_1) != 1)
      {
        printf("Erro: Digite apenas numeros!\n");
        limpar_linha();
        continue;
      }
      limpar_linha();
      if (atacante_idx_1 < 1 || atacante_idx_1 > MAX_TERRITORIOS)
      {
        printf("Selecao invalida. Tente novamente.\n");
        continue;
      }
      if (territorios[atacante_idx_1 - 1].tropas <= 0)
      {
        printf("O atacante selecionado nao possui tropas. Escolha outro.\n");
        continue;
      }
      break;
    }

    /* Seleção do defensor */
    int defensor_idx_1;
    while (1)
    {
      printf("\nSelecione um territorio para defender (DEFENSOR): \n");
      for (int i = 0; i < MAX_TERRITORIOS; i++)
      {
        printf("%d - %s (Cor: %s, Tropas: %d)\n", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
      }
      if (scanf("%d", &defensor_idx_1) != 1)
      {
        printf("Erro: Digite apenas numeros!\n");
        limpar_linha();
        continue;
      }
      limpar_linha();

      if (defensor_idx_1 < 1 || defensor_idx_1 > MAX_TERRITORIOS)
      {
        printf("Selecao invalida. Tente novamente.\n");
        continue;
      }
      if (defensor_idx_1 == atacante_idx_1)
      {
        printf("O territorio defensor nao pode ser o mesmo que o atacante. Tente novamente.\n");
        continue;
      }
      int ai = atacante_idx_1 - 1, di = defensor_idx_1 - 1;
      if (territorios[di].tropas <= 0)
      {
        printf("O defensor selecionado nao possui tropas. Escolha outro.\n");
        continue;
      }
      if (strcmp(territorios[di].cor, territorios[ai].cor) == 0)
      {
        printf("O territorio defensor nao pode ser da mesma cor que o atacante. Tente novamente.\n");
        continue;
      }
      break;
    }

    /* Batalha */
    atacar(&territorios[atacante_idx_1 - 1], &territorios[defensor_idx_1 - 1], rolar_d6);

    /* Pergunta se deseja continuar */
    if (!perguntar_continuar())
      break;
  }

  free(territorios);
  return 0;
}