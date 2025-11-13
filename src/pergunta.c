#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <timer.h>

#include "pergunta.h"
#include "screen.h"
#include "jogador.h"
#include "keyboard.h"

Pergunta *banco_perguntas = NULL;
int total_perguntas = 0;
static int banco_inicializado = 0;
static int semente_inicializada = 0;

static void inicializar_semente()
{
    if (!semente_inicializada)
    {
        srand(time(NULL));
        semente_inicializada = 1;
    }
}

void Pergunta_InicializarBanco()
{
    if (banco_inicializado)
        return;
    Pergunta perguntas_iniciais[] = {
        {"Qual proposição é uma tautologia?",
         {"A) (p V ~p)", "B) (p ^ ~p)", "C) p -> ~p", "D) ~(p <-> q)"},
         0},
        {"Qual proposição é uma contradição?",
         {"A) p -> p", "B) q V p", "C) ~(p -> p)", "D) p <-> p"},
         2},
        {"Qual o resultado de P ^ (P V Q)?",
         {"A) P", "B) Q", "C) P V Q", "D) Tautologia"},
         0}};

    total_perguntas = sizeof(perguntas_iniciais) / sizeof(Pergunta);

    banco_perguntas = (Pergunta *)malloc(total_perguntas * sizeof(Pergunta));
    if (banco_perguntas == NULL)
    {
        fprintf(stderr, "Erro de alocação de memória para o banco de perguntas!\n");
        exit(1);
    }

    memcpy(banco_perguntas, perguntas_iniciais, total_perguntas * sizeof(Pergunta));

    banco_inicializado = 1;
}

void Pergunta_DestruirBanco()
{
    if (banco_perguntas != NULL)
    {
        free(banco_perguntas);
        banco_perguntas = NULL;
    }
    banco_inicializado = 0;
    total_perguntas = 0;
}

void Pergunta_GerarAleatoria(Pergunta *p)
{
    if (!banco_inicializado)
        Pergunta_InicializarBanco();

    int indice = rand() % total_perguntas;

    memcpy(p, &banco_perguntas[indice], sizeof(Pergunta));
}

void Pergunta_DesenharInterface(Pergunta *p)
{
    screenClear();
    screenInit(1);

    int y_start = 5;

    screenSetColor(YELLOW, BLACK);
    screenGotoxy(SCRSTARTX + 5, y_start);
    printf("--- DESAFIO DE LOGICA PROPOSICIONAL (PROF. GUILHERME) ---");
    y_start += 2;

    screenSetColor(WHITE, BLACK);
    screenGotoxy(SCRSTARTX + 5, y_start);
    printf("Proposição:");
    y_start++;
    screenGotoxy(SCRSTARTX + 7, y_start);
    printf("%s", p->texto);
    y_start += 3;

    screenSetColor(LIGHTGRAY, BLACK);
    char labels[] = {'A', 'B', 'C', 'D'};
    for (int i = 0; i < 4; i++)
    {
        screenGotoxy(SCRSTARTX + 5, y_start + i);
        printf("[%c] %s", labels[i], p->opcoes[i]);
    }

    screenGotoxy(SCRSTARTX + 5, y_start + 6);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("Sua Resposta (A/B/C/D): ");

    screenUpdate();
    screenSetNormal();
}

void Pergunta_ProcessarResposta(Jogador *jogador, Pergunta *p, char resposta_usuario)
{
    int resposta_int = toupper(resposta_usuario) - 'A';

    int resultado_y = SCRENDY - 2;

    if (resposta_int == p->resposta_correta)
    {
        jogador->pontuacao += 50;
        screenSetColor(GREEN, BLACK);
        screenGotoxy(SCRSTARTX + 5, resultado_y);
        printf("✅ CORRETO! +50 Pontos. Pressione ENTER para continuar...");
    }
    else
    {
        jogador->vidas -= 1;
        char resposta_certa = 'A' + p->resposta_correta;
        screenSetColor(RED, BLACK);
        screenGotoxy(SCRSTARTX + 5, resultado_y);
        printf("❌ ERRADO! Resposta correta era %c. -1 Vida. Pressione ENTER para continuar...", resposta_certa);
    }

    screenUpdate();

    while (readch() != 10)
    {
    }
}
