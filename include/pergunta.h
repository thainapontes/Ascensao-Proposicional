#ifndef __PERGUNTA_H__
#define __PERGUNTA_H__

#include "tipos.h" // Contém a declaração antecipada e outros tipos
#include "jogador.h" // Para atualizar pontuação/vidas


// O COMPILADOR PRECISA DISSO PARA CRIAR O BANCO DE PERGUNTAS (array) em pergunta.c

typedef struct {
    char *texto; 
    char *opcoes[4]; 
    int respostaCorreta; 
} Pergunta; 


void Pergunta_InicializarBanco();

void Pergunta_DestruirBanco();

void Pergunta_GerarAleatoria(Pergunta *p);

void Pergunta_DesenharInterface(Pergunta *p);

/**
 * Processa a resposta do usuário e atualiza o jogador (pontuação/vida).
 * @param jogador O jogador que respondeu.
 * @param p A pergunta em questão.
 * @param respostaA O caractere da resposta do usuário (ex: 'A', 'B', 'C').
 * @return 1 se a resposta estiver correta, 0 caso contrário.
 */
int Pergunta_ProcessarResposta(Jogador *jogador, Pergunta *p, char respostaA);

#endif // __PERGUNTA_H__
