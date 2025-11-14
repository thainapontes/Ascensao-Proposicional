#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#include "plataforma.h"
#include "pergunta.h"
#include "jogador.h"
#include "tipos.h"
#include "visual.h"

#define NUM_PLATAFORMAS 10
#define TEMPO_ATUALIZACAO 50
#define DISTANCIA_ENTRE_PLATAFORMAS 4
#define PONTUACAO_LIMITE_BONUS 100

static Plataforma plataformas[NUM_PLATAFORMAS];
static Pergunta pergunta_atual;

static void InicializarPlataformas();
static void DesenharHUD(Jogador *jogador);
static void AplicarBonusRecursivo(Jogador *jogador);
static int EncontrarProximaPosicaoY();
static void AtualizarScrollEPlataformas(Jogador *jogador);
static void ProcessarPergunta(Jogador *jogador);

static void InicializarPlataformas()
{
    int y_pos = SCRENDY - 5;

    for (int i = 0; i < NUM_PLATAFORMAS; i++)
    {
        Plataforma_GerarNova(&plataformas[i], y_pos);
        y_pos -= DISTANCIA_ENTRE_PLATAFORMAS;
    }
}

static void DesenharHUD(Jogador *jogador)
{
    screenSetColor(WHITE, BLACK);
    screenGotoxy(SCRSTARTX, SCRSTARTY);
    printf("VIDAS: %d | PONTOS: %d | ALTURA: %d",
           jogador->vidas,
           jogador->pontuacao,
           (SCRENDY - jogador->y));
    screenSetNormal();
}

static void AplicarBonusRecursivo(Jogador *jogador)
{
    int n_fatorial = 3;

    long long bally_bonus = Jogador_CalcularFatorial(n_fatorial);

    jogador->pontuacao += bally_bonus;

    screenGotoxy(SCRSTARTX + 2, SCRENDY - 2);
    screenSetColor(YELLOW, BLACK);
    printf("✨ BÔNUS RECURSIVO! %d! = %lld Pts. Continue!", n_fatorial, bally_bonus);
    screenSetNormal();
    screenUpdate();
    timerSleep(1500);

    jogador->pontuacao_base_bounus = 1;
}

static int EncontrarProximaPosicaoY()
{
    int min_y = SCRENDY;
    for (int i = 0; i < NUM_PLATAFORMAS; i++)
    {
        if (plataformas[i].y < min_y)
        {
            min_y = plataformas[i].y;
        }
    }
    return min_y - DISTANCIA_ENTRE_PLATAFORMAS;
}

static void AtualizarScrollEPlataformas(Jogador *jogador)
{

    const int ALTURA_DE_SCROLL = SCRENDY / 3;

    if (jogador->y < ALTURA_DE_SCROLL)
    {

        int deslocamento = ALTURA_DE_SCROLL - jogador->y;

        jogador->y = ALTURA_DE_SCROLL;

        for (int i = 0; i < NUM_PLATAFORMAS; i++)
        {
            plataformas[i].y += deslocamento;
        }

        jogador->pontuacao += deslocamento;

        for (int i = 0; i < NUM_PLATAFORMAS; i++)
        {

            if (plataformas[i].y > SCRENDY)
            {

                int nova_y = EncontrarProximaPosicaoY();
                Plataforma_GerarNova(&plataformas[i], nova_y);
            }
        }
    }
}

static void ProcessarPergunta(Jogador *jogador)
{
    char resposta_char;
    Pergunta_GerarAleatoria(&pergunta_atual);
    Pergunta_DesenharInterface(&pergunta_atual);
    while (1)
    {
        resposta_char = readch();
        resposta_char = toupper(resposta_char);
        if (resposta_char >= 'A' && resposta_char <= 'D')
        {
            break;
        }
    }

    Pergunta_ProcessarResposta(jogador, &pergunta_atual, resposta_char);
}

void GameLoop(Jogador *jogador)
{

    while (jogador->vidas > 0)
    {
        if (jogador->ativar_pergunta == 1)
        {
            ProcessarPergunta(jogador);
            jogador->ativar_pergunta = 0;
        }
        if (keyhit())
        {
            char key = readch();

            if (key == 'q' || key == 'Q')
                break;
            if (jogador->ativar_pergunta == 0)
            {
                if (key == 'a' || key == 'A')
                {
                    Jogador_MoverHorizontal(jogador, -1);
                }
                else if (key == 'd' || key == 'D')
                {
                    Jogador_MoverHorizontal(jogador, 1);
                }
                else if (key == ' ' || key == 10)
                {
                    Jogador_Pular(jogador);
                }
            }
        }
        if (timerTimeOver())
        {
            Jogador_Atualizar(jogador, plataformas, NUM_PLATAFORMAS);
            AtualizarScrollEPlataformas(jogador);
            if (jogador->pontuacao >= PONTUACAO_LIMITE_BONUS && jogador->pontuacao_base_bounus == 0)
            {
                AplicarBonusRecursivo(jogador);
            }
            screenClear();
            screenInit(1);
            Jogador_Desenhar(jogador);
            for (int i = 0; i < NUM_PLATAFORMAS; i++)
            {
                Plataforma_Desenhar(&plataformas[i]);
            }
            DesenharHUD(jogador);
            Visual_DesenharGuilherme(SCRSTARTX + 5, SCRSTARTY + 1);
            Visual_DesenharDiego(SCRENDX - 7, SCRENDY - 3);

            screenUpdate();
        }
    }
}

int main()
{
    Jogador meu_jogador;
    char simbolo_escolhido;
    printf("--- BEM-VINDO(A) A POUPROSIÇÕES ---\n");
    printf(" Você deverá enfrentar a jornada desesperada para alcançar a Graça Lógica... (Introdução do Jogo)\n");
    printf("Agora, digite o caractere que irá representar seu Jogador (ex: @, P, J): ");
    if (scanf(" %c", &simbolo_escolhido) != 1)
    {
        simbolo_escolhido = '@';
    }
    screenInit(1);
    keyboardInit();
    timerInit(TEMPO_ATUALIZACAO);

    Pergunta_InicializarBanco();
    Jogador_Inicializar(&meu_jogador);

    meu_jogador.simbolo = simbolo_escolhido;
    InicializarPlataformas();
    GameLoop(&meu_jogador);

    screenClear();
    screenDestroy();
    keyboardDestroy();
    timerDestroy();
    Pergunta_DestruirBanco();

    screenGotoxy(SCRSTARTX + 5, SCRENDY / 2);
    printf("FIM DE JOGO! Sua pontuação final: %d\n", meu_jogador.pontuacao);

    fflush(stdout);
    timerSleep(2000);

    return 0;
}
