#include <stdio.h>
#include <stdlib.h> // Para malloc e free
#include <string.h>
#include <time.h>   // Para srand
#include <ctype.h>  // Para toupper
#include <timer.h>

#include "pergunta.h"
#include "screen.h"
#include "jogador.h"
#include "keyboard.h" // Para readch()

// ==========================================================
// VARIÁVEIS GLOBAIS E DE ESTADO (PONTEIROS PARA MALLOC)
// ==========================================================

// O ponteiro que será alocado dinamicamente
Pergunta *banco_perguntas = NULL; 
int total_perguntas = 0; // Armazena o tamanho real do banco
static int banco_inicializado = 0;
static int semente_inicializada = 0;

static void inicializar_semente() {
    if (!semente_inicializada) {
        srand(time(NULL));
        semente_inicializada = 1;
    }
}

// ----------------------------------------------------------
// FUNÇÕES DE INICIALIZAÇÃO E DESTRUIÇÃO (MALLOC / FREE)
// ----------------------------------------------------------

/**
 * Inicializa o banco de perguntas usando alocação dinâmica (MALLOC).
 * Cumpre o requisito de Ponteiros/Alocação Dinâmica.
 */
void Pergunta_InicializarBanco() {
    if (banco_inicializado) return;

    // A. Definição do conteúdo e do tamanho do banco
    // Definimos as perguntas estaticamente AQUI para simplificar a digitação.
    Pergunta perguntas_iniciais[] = {
        {
            "Qual proposição é uma tautologia?",
            {"A) (p V ~p)", "B) (p ^ ~p)", "C) p -> ~p", "D) ~(p <-> q)"},
            0 // Resposta: A
        },
        {
            "Qual proposição é uma contradição?",
            {"A) p -> p", "B) q V p", "C) ~(p -> p)", "D) p <-> p"},
            2 // Resposta: C
        },
        {
            "Qual o resultado de P ^ (P V Q)?",
            {"A) P", "B) Q", "C) P V Q", "D) Tautologia"},
            0 // Resposta: A (Absorção)
        }
    };

    // Calcula o tamanho real do array e o armazena na variável global
    total_perguntas = sizeof(perguntas_iniciais) / sizeof(Pergunta);

    // B. Alocação Dinâmica (MALLOC)
    banco_perguntas = (Pergunta *)malloc(total_perguntas * sizeof(Pergunta));
    if (banco_perguntas == NULL) {
        fprintf(stderr, "Erro de alocação de memória para o banco de perguntas!\n");
        exit(1);
    }
    
    // C. Copia o conteúdo do array estático para o bloco alocado
    memcpy(banco_perguntas, perguntas_iniciais, total_perguntas * sizeof(Pergunta));

    banco_inicializado = 1;
}

/**
 * Libera a memória alocada dinamicamente (FREE).
 * Chamada na finalização do jogo (main.c).
 */
void Pergunta_DestruirBanco() {
    // Uso do FREE para liberar a memória alocada
    if (banco_perguntas != NULL) {
        free(banco_perguntas); 
        banco_perguntas = NULL; // Evita ponteiros pendurados
    }
    banco_inicializado = 0;
    total_perguntas = 0;
}

// ----------------------------------------------------------
// FUNÇÕES DE LÓGICA E INTERFACE
// ----------------------------------------------------------

/**
 * Seleciona uma pergunta aleatória do banco.
 */
void Pergunta_GerarAleatoria(Pergunta *p) {
    if (!banco_inicializado) Pergunta_InicializarBanco();

    // Seleciona um índice aleatório usando o tamanho dinâmico
    int indice = rand() % total_perguntas; 
    
    // Copia a pergunta selecionada (uso de ponteiros e memcpy)
    memcpy(p, &banco_perguntas[indice], sizeof(Pergunta));
}


/**
 * Desenha a interface da pergunta.
 */
void Pergunta_DesenharInterface(Pergunta *p) {
    screenClear();
    screenInit(1); 
    
    int y_start = 5;
    
    screenSetColor(YELLOW, BLACK);
    screenGotoxy(SCRSTARTX + 5, y_start);
    printf("--- DESAFIO DE LOGICA PROPOSICIONAL (PROF. GUILHERME) ---");
    y_start += 2;

    screenSetColor(WHITE, BLACK);
    screenGotoxy(SCRSTARTX + 5, y_start);
    printf("Proposição:");
    y_start++;
    screenGotoxy(SCRSTARTX + 7, y_start);
    printf("%s", p->texto); 
    y_start += 3;

    screenSetColor(LIGHTGRAY, BLACK);
    char labels[] = {'A', 'B', 'C', 'D'};
    for (int i = 0; i < 4; i++) {
        screenGotoxy(SCRSTARTX + 5, y_start + i);
        printf("[%c] %s", labels[i], p->opcoes[i]);
    }
    
    screenGotoxy(SCRSTARTX + 5, y_start + 6);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("Sua Resposta (A/B/C/D): ");
    
    screenUpdate();
    screenSetNormal();
}


/**
 * Processa a resposta do usuário e atualiza o jogador.
 */
void Pergunta_ProcessarResposta(Jogador *jogador, Pergunta *p, char resposta_usuario) {
    int resposta_int = toupper(resposta_usuario) - 'A'; 
    
    int resultado_y = SCRENDY - 2;

    if (resposta_int == p->resposta_correta) {
        jogador->pontuacao += 50; 
        screenSetColor(GREEN, BLACK);
        screenGotoxy(SCRSTARTX + 5, resultado_y);
        printf("✅ CORRETO! +50 Pontos. Pressione ENTER para continuar...");
    } else {
        jogador->vidas -= 1; 
        char resposta_certa = 'A' + p->resposta_correta;
        screenSetColor(RED, BLACK);
        screenGotoxy(SCRSTARTX + 5, resultado_y);
        printf("❌ ERRADO! Resposta correta era %c. -1 Vida. Pressione ENTER para continuar...", resposta_certa);
    }
    
    screenUpdate();
    
    // Espera o usuário pressionar ENTER (código 10)
    while (readch() != 10) {} 
}
