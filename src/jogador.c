#include <stdio.h>
#include <stdlib.h>

#include "jogador.h"
#include "plataforma.h" // NECESSÁRIO para chamar Plataforma_VerificarColisao
#include "screen.h"     // para as constantes SCRSTARTX, SCRENDY, etc.
#include "pergunta.h"   // Para o requisito do projeto

// Constantes de Física
// NOTE: Em sistemas de coordenadas de tela (Y cresce para baixo):
// GRAVIDADE é um valor positivo (puxa para baixo)
// PULO é um valor negativo (puxa para cima)
#define GRAVIDADE 1
#define FORCA_PULO -3
#define POSICAO_REINICIO (SCRENDY - 5)

// ==========================================================
// FUNÇÕES DE INICIALIZAÇÃO E MOVIMENTO
// ==========================================================

void Jogador_Inicializar(Jogador *jogador) {
    int centro_x = SCRSTARTX + (SCRENDX - SCRSTARTX) / 2;
    
    jogador->x = centro_x;
    jogador->y = SCRENDY - 3; 
    jogador->velocidade_y = 0;
    jogador->velocidade_x = 1; 
    jogador->pontuacao = 0;
    jogador->vidas = 3;
    jogador->simbolo = '@';
    jogador->pontuacao_base_bounus = 0;
}

void Jogador_Desenhar(Jogador *jogador) {
    screenSetColor(WHITE, BLACK);
    screenGotoxy(jogador->x, jogador->y);
    printf("%c", jogador->simbolo);
    screenSetNormal();
}

void Jogador_MoverHorizontal(Jogador *jogador, int direcao) {
    jogador->x += jogador->velocidade_x * direcao;
     
    if (jogador->x < SCRSTARTX) {
        jogador->x = SCRSTARTX;
    }
    if (jogador->x >= SCRENDX) { // Usa SCRENDX - 1 se for o limite do caractere
        jogador->x = SCRENDX - 1;
    }
}

void Jogador_Pular(Jogador *jogador) {
    // Só permite pular se estiver parado (velocidade 0)
    if (jogador->velocidade_y == 0) {
        jogador->velocidade_y = FORCA_PULO;
    }
}

// ==========================================================
// FUNÇÃO CRÍTICA: FÍSICA E COLISÃO
// ==========================================================

// Esta função agora recebe o array de Plataformas e seu tamanho
void Jogador_Atualizar(Jogador *jogador, Plataforma plataformas[], int num_plataformas) {
    
    // 1. APLICAÇÃO DA GRAVIDADE E MOVIMENTO
    jogador->velocidade_y += GRAVIDADE;
    jogador->y += jogador->velocidade_y;
    
    // 2. VERIFICAÇÃO DE COLISÃO COM PLATAFORMAS
    // Iteração sobre o array de plataformas (requisito Lógica/Laços)
    for (int i = 0; i < num_plataformas; i++) {
        
        // Colisão é checada APENAS se o jogador estiver caindo (velocidade_y > 0)
        if (jogador->velocidade_y > 0 && Plataforma_VerificarColisao(jogador, &plataformas[i])) {
            
            // Colisão detectada: Pouso
            jogador->velocidade_y = 0;
            jogador->y = plataformas[i].y - 1; // Ajusta o jogador para o topo da plataforma
            
            // Lógica de Interação com Plataformas
            if (plataformas[i].tipo == QUEBRAVEL && plataformas[i].usada == 0) {
                plataformas[i].usada = 1; 
            }
            if (plataformas[i].tipo == PERGUNTA && plataformas[i].usada == 0) {
                // Aqui você chamaria a interface de Pergunta (na etapa de SCROLL/Geração)
                plataformas[i].usada = 1; 
            }
            
            // Pousou em uma, pare de verificar
            break; 
        }
    }
}
    // FUNÇÃO CRÍTICA: FÍSICA E COLISÃO
void Jogador_Atualizar(Jogador *jogador, Plataforma plataformas[], int num_plataformas) {
    
    // 1. APLICAÇÃO DA GRAVIDADE E MOVIMENTO ...
    // ...
    
    // 2. VERIFICAÇÃO DE COLISÃO COM PLATAFORMAS
    for (int i = 0; i < num_plataformas; i++) {
        
        if (jogador->velocidade_y > 0 && Plataforma_VerificarColisao(jogador, &plataformas[i])) {
            
            // Colisão detectada: Pouso ...
            
            // Lógica de Interação com Plataformas
            if (plataformas[i].tipo == QUEBRAVEL && plataformas[i].usada == 0) {
                plataformas[i].usada = 1; 
            }
            
            // Lógica de ATIVAÇÃO DA PERGUNTA
            if (plataformas[i].tipo == PERGUNTA && plataformas[i].usada == 0) {
                // NOTIFICA O MAIN.C que é hora da pergunta
                jogador->ativar_pergunta = 1; // <--- FLAG ATIVADA AQUI
                plataformas[i].usada = 1;      // Marca para não ativar de novo
            }
            
            break; 
        }
    }


    // 3. CHECAGEM DE CHÃO/FIM DE JOGO
    if (jogador->y >= SCRENDY) {
        jogador->vidas--;
        
        // Reinicia o jogador (se ainda houver vidas)
        if (jogador->vidas > 0) {
            jogador->y = POSICAO_REINICIO; 
            jogador->velocidade_y = 0;
        } else {
            // O loop principal em main.c irá encerrar o jogo.
        }
    }

// ==========================================================
// FUNÇÃO RECURSIVA (Obrigatória para PIF)
// ==========================================================
long long Jogador_CalcularFatorial(int n) {
    // 1. Caso Base: Condição de Parada
    if (n == 0) {
        return 1;
    }
    
    // 2. Passo Recursivo: A função chama a si mesma
    // n! = n * (n-1)!
    return (long long)n * Jogador_CalcularFatorial(n - 1);
    }
