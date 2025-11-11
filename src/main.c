#include <stdio.h>
#include <stdlib.h>

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
#define TEMPO_ATUALIZACAO 50 // 50ms = 20 FPS (Frames por segundo)
#define DISTANCIA_ENTRE_PLATAFORMAS 4 
#define PONTUACAO_LIMITE_BONUS 100 // Ativa o bônus quando o jogador alcança esta pontuação

// Variáveis Globais do Módulo (visíveis apenas em main.c)
static Plataforma plataformas[NUM_PLATAFORMAS]; 

// ==============================================================
// 1. FUNÇÕES DE SUPORTE
// ==============================================================

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
 * Funcao auxiliar para desenhar o HUD (Header-Up Display: Vidas e Pontos).
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
 * Funcao auxiliar para aplicar o bonus recursivo.
 */
static void AplicarBonusRecursivo(Jogador *jogador) {
    // Usa um valor fixo (ex: 3) para demonstrar o cálculo fatorial (3! = 6)
    int n_fatorial = 3; 
    
    // CHAMADA RECURSIVA OBRIGATÓRIA PARA PIF
    long long bally_bonus = Jogador_CalcularFatorial(n_fatorial); 
    
    jogador->pontuacao += bally_bonus;

    // Alerta na tela
    screenGotoxy(SCRSTARTX + 2, SCRENDY - 2);
    screenSetColor(YELLOW, BLACK);
    printf("✨ BÔNUS RECURSIVO! %d! = %lld Pts. Continue!", n_fatorial, bally_bonus);
    screenSetNormal();
    screenUpdate();
    timerSleep(1500); // Pausa para ver a mensagem
    
    // Marca que o bônus já foi dado para evitar repetição infinita
    jogador->pontuacao_base_bounus = 1; 
}


// ==============================================================
// 2. O GAME LOOP PRINCIPAL
// ==============================================================

void GameLoop(Jogador *jogador) {
    
    while (jogador->vidas > 0) { 
        
        // 1. PROCESSAMENTO DE INPUT (Teclado)
        if (keyhit()) {
            char key = readch();
            
            if (key == 'q' || key == 'Q') 
                break; 
            
            if (key == 'a' || key == 'A') {
                Jogador_MoverHorizontal(jogador, -1); 
            } else if (key == 'd' || key == 'D') {
                Jogador_MoverHorizontal(jogador, 1);  
            } else if (key == ' ' || key == 10) { 
                Jogador_Pular(jogador);
            }
        }
        
        // 2. LÓGICA DE TEMPO E ATUALIZAÇÃO (FPS)
        if (timerTimeOver()) {
            
            // ATUALIZAÇÃO DO JOGADOR (Física e Colisões)
            Jogador_Atualizar(jogador, plataformas, NUM_PLATAFORMAS); 
            
            // LÓGICA RECURSIVA: Concessão do Bônus uma única vez
            if (jogador->pontuacao >= PONTUACAO_LIMITE_BONUS && jogador->pontuacao_base_bounus == 0) {
                AplicarBonusRecursivo(jogador);
            }
            
            // 3. ATUALIZAÇÃO DA TELA (Desenho)
            screenClear(); 
            screenInit(1); // Redesenha bordas
            
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
// 3. FUNÇÃO PRINCIPAL
// ==============================================================

int main() {
    Jogador meu_jogador;
    char simbolo_escolhido;

    // A. FASE DE CONFIGURAÇÃO (Pré-Inicialização Gráfica)
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
    
    // Pequena pausa para o usuário ver a pontuação final no console antes de fechar
    fflush(stdout); 
    timerSleep(2000); 
    
    return 0;
}
