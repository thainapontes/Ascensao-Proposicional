#ifndef PERGUNTA_H
#define PERGUNTA_H
#include "jogador.h"
#include "tipos.h" // Inclui os ENUMs e struct Jogador

// Definição da estrutura para uma única Pergunta
typedef struct Pergunta {
    char *texto;            // Ponteiro para o texto principal da pergunta
    char *opcoes[4];        // Array de ponteiros para as opções (A, B, C, D)
    int resposta_correta;   // Índice da resposta correta (0 a 3)
} Pergunta;

// Variáveis Globais (Gerenciadas pelo módulo Pergunta)
// O array de structs que será alocado dinamicamente
extern Pergunta *banco_perguntas; 
extern int total_perguntas;

// Protótipos das funções
void Pergunta_InicializarBanco();
void Pergunta_DestruirBanco();
void Pergunta_GerarAleatoria(Pergunta *dest);
void Pergunta_DesenharInterface(Pergunta *p);
void Pergunta_ProcessarResposta(Jogador *j, Pergunta *p, char resposta_usuario);

#endif // PERGUNTA_H
