#ifndef PERGUNTA_H
#define PERGUNTA_H
#include "jogador.h"
#include "tipos.h"

typedef struct Pergunta
{
    char *texto;
    char *opcoes[4];
    int resposta_correta;
} Pergunta;

extern Pergunta *banco_perguntas;
extern int total_perguntas;

void Pergunta_InicializarBanco();
void Pergunta_DestruirBanco();
void Pergunta_GerarAleatoria(Pergunta *dest);
void Pergunta_DesenharInterface(Pergunta *p);
void Pergunta_ProcessarResposta(Jogador *j, Pergunta *p, char resposta_usuario);

#endif
