#include <stdio.h>
#include <stdlib.h>
#include "jogador.h"
#include "plataforma.h"
#include "screen.h"
#include "pergunta.h"

#define GRAVIDADE 1
#define FORCA_PULO -3
#define POSICAO_REINICIO (SCRENDY - 5)

void Jogador_Inicializar(Jogador *jogador)
{
    int centro_x = SCRSTARTX + (SCRENDX - SCRSTARTX) / 2;

    jogador->x = centro_x;
    jogador->y = SCRENDY - 3;
    jogador->velocidade_y = 0;
    jogador->velocidade_x = 1;
    jogador->pontuacao = 0;
    jogador->vidas = 3;
    jogador->simbolo = '@';
    jogador->pontuacao_base_bounus = 0;
}

void Jogador_Desenhar(Jogador *jogador)
{
    screenSetColor(WHITE, BLACK);
    screenGotoxy(jogador->x, jogador->y);
    printf("%c", jogador->simbolo);
    screenSetNormal();
}

void Jogador_MoverHorizontal(Jogador *jogador, int direcao)
{

    jogador->x += jogador->velocidade_x * direcao;

    if (jogador->x < SCRSTARTX)
    {
        jogador->x = SCRSTARTX;
    }

    if (jogador->x >= SCRENDX)
    {
        jogador->x = SCRENDX - 1;
    }
}

void Jogador_Pular(Jogador *jogador)
{
    if (jogador->velocidade_y == 0)
    {
        jogador->velocidade_y = FORCA_PULO;
    }
}

void Jogador_Atualizar(Jogador *jogador, Plataforma plataformas[], int num_plataformas)
{
    jogador->velocidade_y += GRAVIDADE;
    jogador->y += jogador->velocidade_y;
    for (int i = 0; i < num_plataformas; i++)
    {
        if (jogador->velocidade_y > 0 && Plataforma_VerificarColisao(jogador, &plataformas[i]))
        {
            jogador->velocidade_y = 0;
            jogador->y = plataformas[i].y - 1;
            if (plataformas[i].tipo == QUEBRAVEL && plataformas[i].usada == 0)
            {
                plataformas[i].usada = 1;
            }
            if (plataformas[i].tipo == PERGUNTA && plataformas[i].usada == 0)
            {
                plataformas[i].usada = 1;
            }
            break;
        }
    }
    if (jogador->y >= SCRENDY)
    {
        jogador->vidas--;
        if (jogador->vidas > 0)
        {
            jogador->y = POSICAO_REINICIO;
            jogador->velocidade_y = 0;
        }
        else
        {
        }
    }
}
long long Jogador_CalcularFatorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return (long long)n * Jogador_CalcularFatorial(n - 1);
}
