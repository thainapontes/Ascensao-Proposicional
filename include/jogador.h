#ifndef __JOGADOR_H__
#define __JOGADOR_H__

#include "tipos.h"

// definiçao struct jogador
struct Jogador {
    int x; // Posição horizontal na tela
    int y; // Posição vertical na tela
    int velocidade_y; //  Campo para simulação de física (aq ele vai simular queda e pulo)
    int pontuacao;
    int vidas;
    char simbolo; 
};

// apenas o prototipo das funções, para a maquina saber  q elas existem
void Jogador_Inicializar(Jogador *jogador);
void Jogador_Atualizar(Jogador *jogador, Plataforma *plataformas);
void Jogador_MoverHorizontal(Jogador *jogador, int direcao);

#endif // __JOGADOR_H__
