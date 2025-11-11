#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Necessário para toupper (se for usado na lógica de resposta)

// Módulos da CLI-lib
#include "screen.h"     
#include "keyboard.h"   
#include "timer.h"      

// Módulos do Jogo
#include "tipos.h"      
#include "jogador.h"
#include "plataforma.h"
#include "pergunta.h"
#include "visual.h"     

#define NUM_PLATAFORMAS 10 
#define TEMPO_ATUALIZACAO 50 // 50ms = 20 FPS
#define DISTANCIA_ENTRE_PLATAFORMAS 4 
#define PONTUACAO_LIMITE_BONUS 100 // Ativa o bônus quando o jogador alcança esta pontuação

// ==============================================================
// VARIÁVEIS DE ESTADO E FUNÇÕES AUXILIARES PRIVADAS (STATIC)
// ==============================================================

static Plataforma plataformas[NUM_PLATAFORMAS]; 
static Pergunta pergunta_atual; // Armazena a pergunta ativa

// Protótipos das funções auxiliares (para uso interno)
static void InicializarPlataformas();
static void DesenharHUD(Jogador *jogador);
static void AplicarBonusRecursivo(Jogador *jogador);
static int EncontrarProximaPosicaoY();
static void AtualizarScrollEPlataformas(Jogador *jogador);
static void ProcessarPergunta(Jogador *jogador); // <--- NOVO PROTÓTIPO

// -------------------------------------------------------------
// IMPLEMENTAÇÕES DAS FUNÇÕES AUXILIARES
// -------------------------------------------------------------

/**
 * Funcao auxiliar para gerar o conjunto inicial de plataformas.
 */
static void InicializarPlataformas() {
    int y_pos = SCRENDY - 5; 
    
    for (int i = 0; i < NUM_PLATAFORMAS; i++) {
        Plataforma_GerarNova(&plataformas[i], y_pos);
        y_pos -= DISTANCIA_ENTRE_PLATAFORMAS; 
    }
}

/**
 * Funcao auxiliar para desenhar o HUD.
 */
static void DesenharHUD(Jogador *jogador) {
    screenSetColor(WHITE, BLACK);
    screenGotoxy(SCRSTARTX, SCRSTARTY); 
    printf("VIDAS: %d | PONTOS: %d | ALTURA: %d", 
           jogador->vidas, 
           jogador->pontuacao, 
           (SCRENDY - jogador->y));
    screenSetNormal();
}

/**
 * Funcao auxiliar para aplicar o bonus recursivo (PIF Requisito).
 */
static void AplicarBonusRecursivo(Jogador *jogador) {
    int n_fatorial = 3; 
    
    long long bally_bonus = Jogador_CalcularFatorial(n_fatorial); 
    
    jogador->pontuacao += bally_bonus;

    screenGotoxy(SCRSTARTX + 2, SCRENDY - 2);
    screenSetColor(YELLOW, BLACK);
    printf("✨ BÔNUS RECURSIVO! %d! = %lld Pts. Continue!", n_fatorial, bally_bonus);
    screenSetNormal();
    screenUpdate();
    timerSleep(1500); 
    
    jogador->pontuacao_base_bounus = 1; 
}


/**
 * Função auxiliar que encontra a próxima posição Y para gerar uma nova plataforma.
 */
static int EncontrarProximaPosicaoY() {
    int min_y = SCRENDY;
    for (int i = 0; i < NUM_PLATAFORMAS; i++) {
        if (plataformas[i].y < min_y) {
            min_y = plataformas[i].y;
        }
    }
    return min_y - DISTANCIA_ENTRE_PLATAFORMAS; 
}


/**
 * Lógica principal para o Scroll Vertical e Geração Contínua de Plataformas.
 */
static void AtualizarScrollEPlataformas(Jogador *jogador) {
    
    const int ALTURA_DE_SCROLL = SCRENDY / 3;
    
    if (jogador->y < ALTURA_DE_SCROLL) {
        
        int deslocamento = ALTURA_DE_SCROLL - jogador->y;
        
        jogador->y = ALTURA_DE_SCROLL; 

        for (int i = 0; i < NUM_PLATAFORMAS; i++) {
            plataformas[i].y += deslocamento;
        }

        jogador->pontuacao += deslocamento; 
        
        for (int i = 0; i < NUM_PLATAFORMAS; i++) {
            
            if (plataformas[i].y > SCRENDY) {
                
                int nova_y = EncontrarProximaPosicaoY();
                Plataforma_GerarNova(&plataformas[i], nova_y);
            }
        }
    }
}

/**
 * LÓGICA DE PERGUNTA: Pausa o jogo e gerencia o ciclo de input/processamento.
 */
static void ProcessarPergunta(Jogador *jogador) {
    char resposta_char;

    // 1. Gera e Desenha a interface (oculta a tela de jogo, mostra a pergunta)
    Pergunta_GerarAleatoria(&pergunta_atual);
    Pergunta_DesenharInterface(&pergunta_atual);
    
    // 2. Coleta a resposta (pausa o Game Loop até receber A, B, C, ou D)
    while (1) { 
        resposta_char = readch();
        resposta_char = toupper(resposta_char); // Converte para maiúscula
        
        if (resposta_char >= 'A' && resposta_char <= 'D') {
            break;
        }
    }
    
    // 3. Processa a resposta e atualiza o estado do jogador (vidas/pontos)
    // Esta função deve mostrar o resultado e esperar o ENTER do usuário.
    Pergunta_ProcessarResposta(jogador, &pergunta_atual, resposta_char);

    // O Game Loop será retomado quando esta função terminar.
}

// ==============================================================
// 3. O GAME LOOP PRINCIPAL
// ==============================================================

void GameLoop(Jogador *jogador) {
    
    while (jogador->vidas > 0) { 
        
        // --- 3.1 LÓGICA DE PERGUNTA ---
        // A Flag é ativada em Jogador_Atualizar quando toca na plataforma PERGUNTA
        if (jogador->ativar_pergunta == 1) {
            // AQUI O JOGO PAUSA E A INTERFACE DE PERGUNTA É ATIVADA
            ProcessarPergunta(jogador);
            jogador->ativar_pergunta = 0; // Reseta a flag
        }
        
        // 1. PROCESSAMENTO DE INPUT (Teclado)
        if (keyhit()) {
            char key = readch();
            
            if (key == 'q' || key == 'Q') 
                break; 
            
            // Movimentos são processados SOMENTE se o jogo não estiver no modo Pergunta
            if (jogador->ativar_pergunta == 0) {
                 if (key == 'a' || key == 'A') {
                    Jogador_MoverHorizontal(jogador, -1); 
                } else if (key == 'd' || key == 'D') {
                    Jogador_MoverHorizontal(jogador, 1);  
                } else if (key == ' ' || key == 10) { 
                    Jogador_Pular(jogador);
                }
            }
        }
        
        // 2. LÓGICA DE TEMPO E ATUALIZAÇÃO (FPS)
        if (timerTimeOver()) {
            
            // 2.1 Atualiza a física do jogador (gravidade e colisão)
            Jogador_Atualizar(jogador, plataformas, NUM_PLATAFORMAS); 
            
            // 2.2 Lógica de Scroll e Geração Contínua
            AtualizarScrollEPlataformas(jogador);
            
            // 2.3 Lógica de Bônus Recursivo
            if (jogador->pontuacao >= PONTUACAO_LIMITE_BONUS && jogador->pontuacao_base_bounus == 0) {
                AplicarBonusRecursivo(jogador);
            }
            
            // 3. ATUALIZAÇÃO DA TELA (Desenho)
            screenClear(); 
            screenInit(1); 
            
            // Desenha objetos do jogo
            Jogador_Desenhar(jogador);
            for (int i = 0; i < NUM_PLATAFORMAS; i++) {
                Plataforma_Desenhar(&plataformas[i]);
            }
            
            // Desenha HUD e Ícones Estáticos
            DesenharHUD(jogador);
            Visual_DesenharGuilherme(SCRSTARTX + 5, SCRSTARTY + 1);
            Visual_DesenharDiego(SCRENDX - 7, SCRENDY - 3);
            
            screenUpdate(); 
        }
    }
}

// ==============================================================
// 4. FUNÇÃO PRINCIPAL
// ==============================================================

int main() {
    Jogador meu_jogador;
    char simbolo_escolhido;

    // A. FASE DE CONFIGURAÇÃO (Coleta de Dados)
    printf("--- BEM-VINDO(A) A POUPROSIÇÕES ---\n");
    printf(" Você deverá enfrentar a jornada desesperada para alcançar a Graça Lógica... (Introdução do Jogo)\n");
    printf("Agora, digite o caractere que irá representar seu Jogador (ex: @, P, J): ");
    
    if (scanf(" %c", &simbolo_escolhido) != 1) {
        simbolo_escolhido = '@';
    }

    // B. FASE DE INICIALIZAÇÃO DO AMBIENTE
    screenInit(1); 
    keyboardInit(); 
    timerInit(TEMPO_ATUALIZACAO); 
    
    Pergunta_InicializarBanco(); 
    Jogador_Inicializar(&meu_jogador);
    
    meu_jogador.simbolo = simbolo_escolhido; 
    InicializarPlataformas(); 

    // C. INÍCIO DO JOGO
    GameLoop(&meu_jogador);

    // D. FASE DE FINALIZAÇÃO (Limpeza)
    screenClear();
    screenDestroy();
    keyboardDestroy();
    timerDestroy();
    Pergunta_DestruirBanco();

    screenGotoxy(SCRSTARTX + 5, SCRENDY / 2);
    printf("FIM DE JOGO! Sua pontuação final: %d\n", meu_jogador.pontuacao);
    
    fflush(stdout); 
    timerSleep(2000); 
    
    return 0;
}
