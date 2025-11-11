#include "pergunta.h"
#include "screen.h"
#include "jogador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para a função toupper()

// ---------------------------------
// BANCO DE DADOS E VARIÁVEIS GLOBAIS
// ---------------------------------

// Definição estática do banco de perguntas (para simplificar a Entrega 2)
#define NUM_MAX_PERGUNTAS 5
static Pergunta banco_perguntas[NUM_MAX_PERGUNTAS];
static int banco_inicializado = 0;

/**
 * Implementação do Banco de Dados de Perguntas Lógicas (PIF).
 * Você expandirá esta função para incluir mais complexidade (P, Q, ^, V, ->, <->).
 */
void Pergunta_InicializarBanco() {
    if (banco_inicializado) return;

    // Pergunta 1: Tautologia Simples
    banco_perguntas[0].texto = "Qual proposição é uma tautologia?";
    banco_perguntas[0].opcoes[0] = "A) (p V ~p)"; // Correta
    banco_perguntas[0].opcoes[1] = "B) (p ^ ~p)";
    banco_perguntas[0].opcoes[2] = "C) p -> ~p";
    banco_perguntas[0].opcoes[3] = "D) ~(p <-> q)";
    banco_perguntas[0].respostaCorreta = 0;

    // Pergunta 2: Contradição
    banco_perguntas[1].texto = "Qual proposição é uma contradição?";
    banco_perguntas[1].opcoes[0] = "A) p -> p";
    banco_perguntas[1].opcoes[1] = "B) q V p";
    banco_perguntas[1].opcoes[2] = "C) ~(p -> p)"; // Correta
    banco_perguntas[1].opcoes[3] = "D) p <-> p";
    banco_perguntas[1].respostaCorreta = 2;
    
    // Pergunta 3: (Exemplo)
    banco_perguntas[2].texto = "Qual o resultado de P ^ (P V Q)?";
    banco_perguntas[2].opcoes[0] = "A) P"; // Correta
    banco_perguntas[2].opcoes[1] = "B) Q";
    banco_perguntas[2].opcoes[2] = "C) P V Q";
    banco_perguntas[2].opcoes[3] = "D) Tautologia";
    banco_perguntas[2].respostaCorreta = 0;
    
    // ... adicione mais perguntas

    banco_inicializado = 1;
}

void Pergunta_DestruirBanco() {
    // Não é necessário liberar memória se não usamos malloc, mas mantém o protótipo.
    banco_inicializado = 0;
}

/**
 * Seleciona uma pergunta aleatória do banco.
 */
void Pergunta_GerarAleatoria(Pergunta *p) {
    if (!banco_inicializado) Pergunta_InicializarBanco();

    // Seleciona um índice aleatório
    int indice = rand() % NUM_MAX_PERGUNTAS;
    
    // Copia os dados da pergunta do banco para a struct local 'p'
    // Como estamos usando ponteiros char* (strings estáticas), copiamos as referências.
    p->texto = banco_perguntas[indice].texto;
    for (int i = 0; i < 4; i++) {
        p->opcoes[i] = banco_perguntas[indice].opcoes[i];
    }
    p->respostaCorreta = banco_perguntas[indice].respostaCorreta;
}


/**
 * Desenha a interface da pergunta.
 */
void Pergunta_DesenharInterface(Pergunta *p) {
    // 1. Limpa a tela e desenha as bordas para a interface da pergunta
    screenClear();
    screenInit(1); // Redesenha bordas

    screenSetColor(YELLOW, BLACK);
    screenGotoxy(SCRSTARTX + 5, SCRSTARTY + 2);
    printf("--- DESAFIO DE LOGICA PROPOSICIONAL (PROF. GUILHERME) ---");

    screenSetColor(WHITE, BLACK);
    // Exibe a Pergunta
    screenGotoxy(SCRSTARTX + 2, SCRSTARTY + 4);
    printf("%s", p->texto);

    // Exibe as Opções de Múltipla Escolha
    for (int i = 0; i < 4; i++) {
        screenGotoxy(SCRSTARTX + 4, SCRSTARTY + 6 + i);
        printf("%s", p->opcoes[i]);
    }
    
    screenSetColor(LIGHTCYAN, BLACK);
    screenGotoxy(SCRSTARTX + 2, SCRSTARTY + 12);
    printf("Sua Resposta (A/B/C/D): ");
    screenSetNormal();
    screenUpdate();
}

/**
 * Processa a resposta do usuário e atualiza o jogador.
 */
int Pergunta_ProcessarResposta(Jogador *jogador, Pergunta *p, char respostaA) {
    // 1. Converte a resposta do usuário (char) em um índice (0, 1, 2, 3)
    // 'A' -> 0, 'B' -> 1, etc.
    int indice_resposta = toupper(respostaA) - 'A';
    
    int correto = 0;

    // 2. Compara o índice da resposta com o índice correto da pergunta
    if (indice_resposta == p->respostaCorreta) {
        correto = 1;
        jogador->pontuacao += 10; // Recompensa por acerto
        
        screenSetColor(GREEN, BLACK);
        screenGotoxy(SCRSTARTX + 2, SCRENDY - 2);
        printf("CORRETO! +10 Pontos. Pressione ENTER para continuar.");
        
    } else {
        jogador->vidas--; // Penalidade por erro
        
        screenSetColor(RED, BLACK);
        screenGotoxy(SCRSTARTX + 2, SCRENDY - 2);
        printf("ERRADO! Resposta correta: %s. Pressione ENTER para continuar.", p->opcoes[p->respostaCorreta]);
    }

    screenSetNormal();
    
    // Espera o usuário pressionar ENTER para continuar (retorna ao jogo)
    // Este é um procedimento de pausa comum em jogos de terminal.
    readch(); 
    
    return correto;
}
