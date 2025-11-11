#ifndef __PERGUNTA_H__
#define __PERGUNTA_H__

#include "tipos.h" 
#include "jogador.h" // Pode ser necessário para atualizar a pontuação/vidas

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
