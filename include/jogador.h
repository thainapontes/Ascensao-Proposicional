#ifndef __JOGADOR_H__
#define __JOGADOR_H__

#include "tipos.h"
#include "plataforma.h"

typedef struct Jogador
{
    int x;
    int y;
    int velocidade_y;
    int velocidade_x;
    int vidas;
    int pontuacao;
    char simbolo;
    int pontuacao_base_bounus;
    int ativar_pergunta;
} Jogador;

void Jogador_Inicializar(Jogador *jogador);
void Jogador_Atualizar(Jogador *j, Plataforma plataformas[], int num_plataformas);
void Jogador_Pular(Jogador *j);
void Jogador_Desenhar(Jogador *j);
void Jogador_MoverHorizontal(Jogador *jogador, int direcao);
long long Jogador_CalcularFatorial(int n);

#endif
