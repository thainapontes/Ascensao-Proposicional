#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "plataforma.h"
#include "screen.h"
#include "jogador.h"

static int semente_inicializada = 0;
static void inicializar_semente()
{
    if (!semente_inicializada)
    {
        srand(time(NULL));
        semente_inicializada = 1;
    }
}

void Plataforma_GerarNova(Plataforma *p, int y_inicial)
{
    inicializar_semente();

    p->x = SCRSTARTX + (rand() % (SCRENDX - SCRSTARTX - 5));
    p->y = y_inicial;
    p->largura = 8 + (rand() % 5);

    int chance = rand() % 100;

    if (chance < 80)
    {
        p->tipo = NORMAL;
    }
    else if (chance < 90)
    {
        p->tipo = PERGUNTA;
    }
    else
    {
        p->tipo = QUEBRAVEL;
    }

    p->usada = 0;
}

void Plataforma_Desenhar(Plataforma *p)
{
    if (p->tipo == QUEBRAVEL && p->usada == 1)
    {
        return;
    }

    char caractere = BOX_HLINE;
    screenColor cor = GREEN;
    switch (p->tipo)
    {
    case NORMAL:
        cor = GREEN;
        caractere = BOX_HLINE;
        break;
    case PERGUNTA:
        cor = BLUE;
        caractere = '?';
        break;
    case QUEBRAVEL:
        cor = LIGHTGRAY;
        caractere = BOX_DIAMOND;
        break;
    case PROP_LOGICA:
        cor = YELLOW;
        caractere = BOX_BLOCK;
        break;
    }

    screenSetColor(cor, BLACK);
    screenBoxEnable();

    for (int i = 0; i < p->largura; i++)
    {
        screenGotoxy(p->x + i, p->y);
        if (p->tipo == PERGUNTA && i != p->largura / 2)
        {
            printf("%c", BOX_HLINE);
        }
        else
        {
            printf("%c", caractere);
        }
    }

    screenBoxDisable();
    screenSetNormal();
}

int Plataforma_VerificarColisao(Jogador *jogador, Plataforma *p)
{
    if (p->usada && p->tipo == QUEBRAVEL)
    {
        return 0;
    }
    if (jogador->velocidade_y > 0 && jogador->y == (p->y - 1))
    {
        if (jogador->x >= p->x && jogador->x < (p->x + p->largura))
        {
            if (p->tipo == QUEBRAVEL)
            {
                p->usada = 1;
            }
            return 1;
        }
    }
    return 0;
}
