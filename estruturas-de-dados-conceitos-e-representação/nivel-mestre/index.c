// Sistema War estruturado: Missões estratégicas (nível mestre)
// Requisitos: modularização, uso de ponteiros, alocação dinâmica, srand/rand, verificação de missão

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura base do jogo
typedef struct {
	char nome[30];
	char cor[10];
	int tropas;
} Territorio;

// Estrutura auxiliar do jogador
typedef struct {
	char nome[30];
	char cor[10];
	char* missao; // armazenada dinamicamente
} Jogador;

// Variável global apenas para simplificar a assinatura pedida de verificarMissao
// Ao verificar a missão de um jogador, ajustamos esta cor antes de chamar a função.
static const char* g_corJogadorAtual = NULL;

// Assinaturas das funções (modularização)
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void exibirMissao(const char* nomeJogador, const char* missao);
void exibirMapa(Territorio* mapa, int tamanho);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa, int tamanhoMapa, Jogador* jogadores, int qtdJogadores);

// --- Implementações ---

// Escolhe aleatoriamente uma missão do vetor e copia para o destino usando strcpy.
// Observação: destino deve apontar para memória previamente alocada.
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
	if (!destino || !missoes || totalMissoes <= 0) return;
	int idx = rand() % totalMissoes;
	strcpy(destino, missoes[idx]);
}

// Exibe a missão apenas para o jogador, no início do jogo.
void exibirMissao(const char* nomeJogador, const char* missao) {
	if (!nomeJogador || !missao) return;
	printf("\n[Missão de %s]: %s\n\n", nomeJogador, missao);
}

// Mostra um resumo do mapa.
void exibirMapa(Territorio* mapa, int tamanho) {
	printf("\n=== Mapa ===\n");
	for (int i = 0; i < tamanho; i++) {
		printf("%d) %-15s | Cor: %-9s | Tropas: %d\n",
			   i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
	}
}

// Simula um ataque entre territórios usando rolagem de dados (1 a 6).
// Regras:
// - Só é válido atacar se as cores forem diferentes (território inimigo)
// - Se atacante vence: defensor muda de cor para a do atacante e recebe metade das tropas do atacante
//   (movimentação), que são retiradas do território atacante.
// - Se perde: o atacante perde 1 tropa (mínimo de 1 tropa no território atacante).
void atacar(Territorio* atacante, Territorio* defensor) {
	if (!atacante || !defensor) return;

	if (strcmp(atacante->cor, defensor->cor) == 0) {
		printf("Ataque inválido: não é possível atacar território da mesma cor.\n");
		return;
	}

	if (atacante->tropas <= 1) {
		printf("Ataque inválido: o território atacante precisa de mais de 1 tropa.\n");
		return;
	}

	int dadoAtacante = (rand() % 6) + 1;
	int dadoDefensor = (rand() % 6) + 1;

	printf("Rolagens -> Atacante: %d | Defensor: %d\n", dadoAtacante, dadoDefensor);

	if (dadoAtacante > dadoDefensor) {
		// Vitória do atacante: conquista o território
		int mover = atacante->tropas / 2; // metade arredondada para baixo
		if (mover < 1) mover = 1; // garante ao menos 1

		// Captura
		strncpy(defensor->cor, atacante->cor, sizeof(defensor->cor) - 1);
		defensor->cor[sizeof(defensor->cor) - 1] = '\0';
		defensor->tropas = mover; // recebe a metade do atacante

		atacante->tropas -= mover;
		if (atacante->tropas < 1) atacante->tropas = 1; // mantém ao menos 1 tropa

		printf("Conquista! %s agora pertence à cor %s com %d tropas.\n",
			   defensor->nome, defensor->cor, defensor->tropas);
	} else {
		// Derrota do atacante
		atacante->tropas -= 1;
		if (atacante->tropas < 1) atacante->tropas = 1;
		printf("Defesa bem sucedida! O atacante perde 1 tropa e fica com %d.\n", atacante->tropas);
	}
}

// Verifica o cumprimento da missão do jogador.
// IMPORTANTE: utiliza g_corJogadorAtual para identificar qual cor deve ser considerada como do jogador.
// Missões suportadas (exemplos):
// - "Controlar ao menos 3 territorios"
// - "Eliminar todas as tropas inimigas" (inimigo sem territórios)
// - "Manter pelo menos 15 tropas no total"
// - "Ter um territorio com 8 ou mais tropas"
// - "Controlar todos os territorios"
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
	if (!missao || !mapa || tamanho <= 0 || !g_corJogadorAtual) return 0;

	// Contagens úteis
	int totalDoJogador = 0;
	int totalTropasDoJogador = 0;
	int totalTerritorios = tamanho;
	int totalDoInimigo = 0;

	// Identifica inimigo como qualquer cor diferente da do jogador
	// Observação: caso existam múltiplas cores, consolidamos como "inimigo > 0".
	for (int i = 0; i < tamanho; i++) {
		if (strcmp(mapa[i].cor, g_corJogadorAtual) == 0) {
			totalDoJogador++;
			totalTropasDoJogador += mapa[i].tropas;
		} else {
			totalDoInimigo++;
		}
	}

	// Normalizamos missão para comparações simples por substring
	// (mantemos em português como no vetor de exemplos)
	if (strstr(missao, "Controlar ao menos 3 territorios") != NULL) {
		return totalDoJogador >= 3;
	}

	if (strstr(missao, "Eliminar todas as tropas inimigas") != NULL) {
		// Sem territórios do inimigo -> missão cumprida
		return totalDoInimigo == 0;
	}

	if (strstr(missao, "Manter pelo menos 15 tropas no total") != NULL) {
		return totalTropasDoJogador >= 15;
	}

	if (strstr(missao, "Ter um territorio com 8 ou mais tropas") != NULL) {
		for (int i = 0; i < tamanho; i++) {
			if (strcmp(mapa[i].cor, g_corJogadorAtual) == 0 && mapa[i].tropas >= 8) {
				return 1;
			}
		}
		return 0;
	}

	if (strstr(missao, "Controlar todos os territorios") != NULL) {
		return totalDoJogador == totalTerritorios;
	}

	// Caso seja uma missão desconhecida, retornamos não cumprida.
	return 0;
}

// Libera toda memória dinâmica alocada (mapa e missões dos jogadores)
void liberarMemoria(Territorio* mapa, int tamanhoMapa, Jogador* jogadores, int qtdJogadores) {
	(void)tamanhoMapa; // não é necessário aqui, mas mantido por simetria
	if (mapa) free(mapa);
	if (jogadores) {
		for (int i = 0; i < qtdJogadores; i++) {
			free(jogadores[i].missao);
			jogadores[i].missao = NULL;
		}
	}
}

int main(void) {
	srand((unsigned int)time(NULL));

	// Vetor de missões (ao menos 5)
	char* missoes[] = {
		"Controlar ao menos 3 territorios",
		"Eliminar todas as tropas inimigas",
		"Manter pelo menos 15 tropas no total",
		"Ter um territorio com 8 ou mais tropas",
		"Controlar todos os territorios"
	};
	const int totalMissoes = (int)(sizeof(missoes) / sizeof(missoes[0]));

	// Mapa inicial (tamanho pequeno para demonstração)
	const int TAM_MAPA = 6;
	Territorio* mapa = (Territorio*)calloc(TAM_MAPA, sizeof(Territorio));
	if (!mapa) {
		fprintf(stderr, "Erro de alocação do mapa.\n");
		return 1;
	}

	// Inicializa territórios (2 cores: azul e vermelha)
	// Distribuição simples para facilitar testes
	strcpy(mapa[0].nome, "Alfa");   strcpy(mapa[0].cor, "azul");     mapa[0].tropas = 5;
	strcpy(mapa[1].nome, "Beta");   strcpy(mapa[1].cor, "azul");     mapa[1].tropas = 4;
	strcpy(mapa[2].nome, "Gamma");  strcpy(mapa[2].cor, "azul");     mapa[2].tropas = 3;
	strcpy(mapa[3].nome, "Delta");  strcpy(mapa[3].cor, "vermelha"); mapa[3].tropas = 5;
	strcpy(mapa[4].nome, "Epsilon");strcpy(mapa[4].cor, "vermelha"); mapa[4].tropas = 4;
	strcpy(mapa[5].nome, "Zeta");   strcpy(mapa[5].cor, "vermelha"); mapa[5].tropas = 3;

	// Jogadores
	const int QTD_JOGADORES = 2;
	Jogador jogadores[QTD_JOGADORES];

	// Configura jogadores
	strcpy(jogadores[0].nome, "Jogador 1"); strcpy(jogadores[0].cor, "azul");
	strcpy(jogadores[1].nome, "Jogador 2"); strcpy(jogadores[1].cor, "vermelha");

	// Aloca memória para missões e atribui
	for (int i = 0; i < QTD_JOGADORES; i++) {
		jogadores[i].missao = (char*)malloc(128 * sizeof(char));
		if (!jogadores[i].missao) {
			fprintf(stderr, "Erro de alocação da missão do %s.\n", jogadores[i].nome);
			liberarMemoria(mapa, TAM_MAPA, jogadores, QTD_JOGADORES);
			return 1;
		}
		atribuirMissao(jogadores[i].missao, missoes, totalMissoes);
	}

	// Exibe cada missão apenas uma vez (início)
	for (int i = 0; i < QTD_JOGADORES; i++) {
		exibirMissao(jogadores[i].nome, jogadores[i].missao);
	}

	// Loop simples de turnos
	int vencedor = -1;
	int turno = 1;

	while (vencedor == -1) {
		printf("\n===== Turno %d =====\n", turno);

		for (int idxJog = 0; idxJog < QTD_JOGADORES; idxJog++) {
			Jogador* J = &jogadores[idxJog];
			g_corJogadorAtual = J->cor; // define o contexto da verificação de missão

			printf("\nVez de %s (cor: %s)\n", J->nome, J->cor);
			exibirMapa(mapa, TAM_MAPA);

			int desejaAtacar = 0;
			printf("Deseja atacar? (1 = sim, 0 = nao): ");
			if (scanf("%d", &desejaAtacar) != 1) {
				// limpeza básica de entrada inválida
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}
				desejaAtacar = 0;
			}

			if (desejaAtacar == 1) {
				int iAtk = -1, iDef = -1;
				printf("Informe o indice do territorio ATACANTE: ");
				scanf("%d", &iAtk);
				printf("Informe o indice do territorio DEFENSOR: ");
				scanf("%d", &iDef);

				if (iAtk >= 0 && iAtk < TAM_MAPA && iDef >= 0 && iDef < TAM_MAPA) {
					Territorio* A = &mapa[iAtk];
					Territorio* D = &mapa[iDef];
					if (strcmp(A->cor, J->cor) != 0) {
						printf("Ataque invalido: o territorio atacante precisa ser da sua cor (%s).\n", J->cor);
					} else if (strcmp(D->cor, J->cor) == 0) {
						printf("Ataque invalido: o defensor nao pode ser da mesma cor.\n");
					} else {
						atacar(A, D);
					}
				} else {
					printf("Indices invalidos.\n");
				}
			}

			// Verifica missão silenciosamente ao final da jogada do jogador
			if (verificarMissao(J->missao, mapa, TAM_MAPA)) {
				vencedor = idxJog;
				break;
			}
		}

		if (vencedor != -1) break;
		turno++;
	}

	if (vencedor != -1) {
		printf("\n==============================\n");
		printf("VENCEDOR: %s (cor: %s)!\n", jogadores[vencedor].nome, jogadores[vencedor].cor);
		printf("Missao cumprida: %s\n", jogadores[vencedor].missao);
		printf("==============================\n\n");
	}

	liberarMemoria(mapa, TAM_MAPA, jogadores, QTD_JOGADORES);
	return 0;
}

