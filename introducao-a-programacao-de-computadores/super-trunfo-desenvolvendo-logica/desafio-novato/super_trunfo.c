#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

float calculate_density(int population, float area)
{
  return population / area;
}

float calculate_pib_per_capita(float pib, int population)
{
  return pib / population;
}

float calculate_super_power(int population, float area, float pib, int turistic_points, float pib_per_capita, float population_density)
{
  return population + area + pib + turistic_points + pib_per_capita + (1.0 / population_density);
}

int main()
{
  setlocale(LC_ALL, ""); // Permite exibição de caracteres acentuados no Windows

  /* Carta 01 e Carta 02 */
  char state_1[3], state_2[3];
  char card_code_1[4], card_code_2[4];
  char city_name_1[50], city_name_2[50];
  int population_number_1, population_number_2;
  float area_number_1, area_number_2;
  float pib_number_1, pib_number_2;
  float population_density_1, population_density_2;
  float pib_per_capita_1, pib_per_capita_2;
  float super_power_1, super_power_2;
  int turistic_points_1, turistic_points_2;

  /* Entrada de dados da Carta 1 */
  printf("<-Bem-vindo ao Super Trunfo!->\n");
  printf("\nAdicione as informações da carta numero 1:\n");

  /* Entrada de dados da Carta 1 */
  printf("\nEstado (A-H): ");
  scanf(" %s", &state_1);

  printf("Código da carta (ex: A01): ");
  scanf("%s", card_code_1);

  printf("Nome da Cidade: ");
  getchar(); // Remove o \n deixado pelo scanf anterior
  fgets(city_name_1, 100, stdin);

  printf("População: ");
  scanf("%d", &population_number_1);

  printf("Área (em km²): ");
  scanf("%f", &area_number_1);

  printf("PIB (em bilhões de reais): ");
  scanf("%f", &pib_number_1);

  printf("Número de pontos turísticos: ");
  scanf("%d", &turistic_points_1);

  printf("\n-----------------------------\n");

  printf("\nAdicione as informações da carta numero 2:\n");

  /* Entrada de dados da Carta 2 */
  printf("\nEstado (A-H): ");
  scanf(" %s", &state_2);

  printf("Código da carta (ex: B02): ");
  scanf("%s", card_code_2);

  printf("Nome da Cidade: ");
  getchar(); // Remove o \n deixado pelo scanf anterior
  fgets(city_name_2, 100, stdin);

  printf("População: ");
  scanf("%d", &population_number_2);

  printf("Área (em km²): ");
  scanf("%f", &area_number_2);

  printf("PIB (em bilhões de reais): ");
  scanf("%f", &pib_number_2);

  printf("Número de pontos turísticos: ");
  scanf("%d", &turistic_points_2);

  /* Cálculo da densidade populacional */
  population_density_1 = calculate_density(population_number_1, area_number_1);
  population_density_2 = calculate_density(population_number_2, area_number_2);

  /* Cálculo de PIB per capita */
  pib_per_capita_1 = calculate_pib_per_capita(pib_number_1, population_number_1);
  pib_per_capita_2 = calculate_pib_per_capita(pib_number_2, population_number_2);

  /* Cálculo do Super Poder */
  super_power_1 = calculate_super_power(population_number_1, area_number_1, pib_number_1, turistic_points_1, pib_per_capita_1, population_density_1);
  super_power_2 = calculate_super_power(population_number_2, area_number_2, pib_number_2, turistic_points_2, pib_per_capita_2, population_density_2);

  printf("\n-----------------------------\n");

  /* Exibição da Carta 01 */
  printf("\nCarta 1:\n");
  printf("Estado: %s\n", state_1);
  printf("Código: %s\n", card_code_1);
  printf("Nome da Cidade: %s", city_name_1);
  printf("População: %d\n", population_number_1);
  printf("Área: %.2f km²\n", area_number_1);
  printf("PIB: %.2f bilhões de reais\n", pib_number_1);
  printf("Número de Pontos Turísticos: %d\n", turistic_points_1);
  printf("Densidade Populacional: %.2f hab/km²", population_density_1);
  printf("\nPIB per capita: %.2f reais\n", pib_per_capita_1);

  /* Exibição da Carta 02 */
  printf("\nCarta 2:\n");
  printf("Estado: %s\n", state_2);
  printf("Código: %s\n", card_code_2);
  printf("Nome da Cidade: %s", city_name_2);
  printf("População: %d\n", population_number_2);
  printf("Área: %.2f km²\n", area_number_2);
  printf("PIB: %.2f bilhões de reais\n", pib_number_2);
  printf("Número de Pontos Turísticos: %d\n", turistic_points_2);
  printf("Densidade Populacional: %.2f hab/km²", population_density_2);
  printf("\nPIB per capita: %.2f reais", pib_per_capita_2);

  /* Comparação das cartas */
  printf("\n-----------------------------\n");
  printf("\nComparação das Cartas:\n");

  /* População */
  int population_winner = (population_number_1 > population_number_2) ? 1 : 0;
  printf("População: Carta %d vence\n", population_winner ? 1 : 2);

  /* Área */
  int area_winner = (area_number_1 > area_number_2) ? 1 : 0;
  printf("Área: Carta %d vence\n", area_winner ? 1 : 2);

  /* PIB */
  int pib_winner = (pib_number_1 > pib_number_2) ? 1 : 0;
  printf("PIB: Carta %d vence\n", pib_winner ? 1 : 2);

  /* Número de Pontos Turísticos */
  int turistic_points_winner = (turistic_points_1 > turistic_points_2) ? 1 : 0;
  printf("Número de Pontos Turísticos: Carta %d vence\n", turistic_points_winner ? 1 : 2);

  /* Densidade Populacional (menor valor vence) */
  int density_winner = (population_density_1 < population_density_2) ? 1 : 0;
  printf("Densidade Populacional: Carta %d vence\n", density_winner ? 1 : 2);

  /* PIB per capita */
  int pib_per_capita_winner = (pib_per_capita_1 > pib_per_capita_2) ? 1 : 0;
  printf("PIB per capita: Carta %d vence\n", pib_per_capita_winner ? 1 : 2);

  /* Super Poder */
  int super_power_winner = (super_power_1 > super_power_2) ? 1 : 0;
  printf("Super Poder: Carta %d vence\n", super_power_winner ? 1 : 2);

  /* Comparação de cartas (Atributo: População) */
  printf("\n-----------------------------\n");
  printf("\nComparação de cartas (Atributo: População):\n");

  printf("Carta 1 - %s (%s): %d\n", city_name_1, state_1, population_number_1);
  printf("Carta 2 - %s (%s): %d\n", city_name_2, state_2, population_number_2);

  if (population_number_1 > population_number_2) {
    printf("Resultado: Carta 1 (%s) venceu!\n", city_name_1);
  } else {
    printf("Resultado: Carta 2 (%s) venceu!\n", city_name_2);
  }

  return 0;
}
