#ifndef __PLATAFORMA_H__
#define __PLATAFORMA_H__
#include "tipos.h"

// Declaração antecipada de Jogador para evitar inclusão circular
typedef struct Jogador Jogador;

typedef struct Plataforma {
    int x;
    int y;
    int largura;
    TipoPlataforma tipo;
    int usada;
} Plataforma;

void Plataforma_GerarNova(Plataforma *p, int y_inicial);
void Plataforma_Desenhar(Plataforma *p);
int Plataforma_VerificarColisao(Jogador *jogador, Plataforma *p);

#endif
