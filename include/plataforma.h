#ifndef __PLATAFORMA_H__
#define __PLATAFORMA_H__
#include "tipos.h"

// Declaração antecipada de Jogador para evitar inclusão circular
typedef struct Jogador Jogador;

typedef struct Plataforma {
    int x;
    int y;
    int largura;
    TipoPlataforma tipo; // Usa o enum definido em tipos.h
    int usada;           // Flag para plataformas quebráveis
} Plataforma;


void Plataforma_GerarNova(Plataforma *p, int y_inicial);
void Plataforma_Desenhar(Plataforma *p);
int Plataforma_VerificarColisao(Jogador *jogador, Plataforma *p);

#endif 
