#ifndef __JOGADOR_H__
#define __JOGADOR_H__

#include "tipos.h"
#include "plataforma.h"

struct Jogador {
    int x;
    int y;
    int velocidade_y;
    int velocidade_x;
    int vidas;
    int pontuacao;
    char simbolo;
    int pontuacao_base_bounus; // Para o requisito de Recursividade
    int ativar_pergunta;       // <--- NOVO: Flag para comunicar ao main.c
};

// apenas o prototipo das funções, para a maquina saber  q elas existem
void Jogador_Inicializar(Jogador *jogador);
void Jogador_Atualizar(Jogador *j, Plataforma plataformas[], int num_plataformas);
void Jogador_MoverHorizontal(Jogador *jogador, int direcao);
long long Jogador_CalcularFatorial(int n); //RECURSIVIDADE: Calcula o fatorial de um número para pontuação bônus.

#endif 
