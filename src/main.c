#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Protótipos das funções auxiliares (para uso interno)
static void InicializarPlataformas();
static void DesenharHUD(Jogador *jogador);
static void AplicarBonusRecursivo(Jogador *jogador);
static int EncontrarProximaPosicaoY();
static void AtualizarScrollEPlataformas(Jogador *jogador);


/**
 * Funcao auxiliar para gerar o conjunto inicial de plataformas.
 */
static void InicializarPlataformas() {
    int y_pos = SCRENDY - 5; 
    
    // Laço para gerar o primeiro conjunto de plataformas de baixo para cima
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
    
    // CHAMADA RECURSIVA
    long long bally_bonus = Jogador_CalcularFatorial(n_fatorial); 
    
    jogador->pontuacao += bally_bonus;

    // Alerta na tela
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
    // Encontra a plataforma que está mais próxima do topo (menor valor de y)
    for (int i = 0; i < NUM_PLATAFORMAS; i++) {
        if (plataformas[i].y < min_y) {
            min_y = plataformas[i].y;
        }
    }
    // Retorna a posição acima da plataforma mais alta, respeitando a distância
    return min_y - DISTANCIA_ENTRE_PLATAFORMAS; 
}


/**
 * Lógica principal para o Scroll Vertical e Geração Contínua de Plataformas.
 */
static void AtualizarScrollEPlataformas(Jogador *jogador) {
    
    // Altura de Ativação do Scroll (Ex: 1/3 da tela de cima para baixo)
    const int ALTURA_DE_SCROLL = SCRENDY / 3;
    
    // Condição: O jogador passou do limite de scroll e está subindo.
    if (jogador->y < ALTURA_DE_SCROLL) {
        
        // 1. Calcula o deslocamento (quanto o mundo precisa descer)
        int deslocamento = ALTURA_DE_SCROLL - jogador->y;
        
        // 2. MOVE O JOGADOR DE VOLTA (Fixa na posição de scroll)
        jogador->y = ALTURA_DE_SCROLL; 

        // 3. MOVIMENTA TODAS AS PLATAFORMAS (SCROLL)
        for (int i = 0; i < NUM_PLATAFORMAS; i++) {
            plataformas[i].y += deslocamento;
        }

        // 4. ATUALIZAÇÃO DA PONTUAÇÃO (pela distância percorrida)
        jogador->pontuacao += deslocamento; 
        
        // 5. GERAÇÃO CONTÍNUA
        for (int i = 0; i < NUM_PLATAFORMAS; i++) {
            
            // Verifica se a plataforma saiu pela parte inferior da tela
            if (plataformas[i].y > SCRENDY) {
                
                // Regenera a plataforma no topo
                int nova_y = EncontrarProximaPosicaoY();
                Plataforma_GerarNova(&plataformas[i], nova_y);
            }
        }
    }
}


// ==============================================================
// 3. O GAME LOOP PRINCIPAL
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
