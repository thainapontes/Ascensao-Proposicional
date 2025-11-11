#include <stdio.h>
#include <stdlib.h>
#include "jogador.h"
#include "screen.h" // necessário para usar as constantes de tela (SCRSTARTX, SCRENDY, etc.)




#define GRAVIDADE 1 //definiçao da constante da gravidade
#define FORCA_PULO -3 // velocidade inicial negativa para subir

//inicializa a struct do jogador com valores de início 
void Jogador_Inicializar(Jogador *jogador) {
    //posição na tela, onde o jogador deve começar a aparecer
    int centro_x = SCRSTARTX + (SCRENDX - SCRSTARTX) / 2; //constantes de tela lá em screen.h
    
    jogador->x = centro_x;
    jogador->y = SCRENDY - 2; 

    // estado inicial da fisica
    // a velocidade vertical (y) é 0, pois ele está parado ao começar
    jogador->velocidade_y = 0; 

    //estado inicial
    jogador->pontuacao = 0;
    jogador->vidas = 3; // Geralmente começa com 3 vidas.
    jogador->simbolo = '@'; // O caractere que o representa na tela.
}

//esse procedimento move o jogador horizontalmente e verifica os limites da tela.
 void Jogador_MoverHorizontal(Jogador *jogador, int direcao) { 
    // Atualiza a posição X
    jogador->x += direcao;
    
    // Verifica os limites da área de jogo (SCRSTARTX e SCRENDX)
    if (jogador->x < SCRSTARTX) {
        jogador->x = SCRSTARTX;
    }
    if (jogador->x > SCRENDX) {
        jogador->x = SCRENDX;
    }
}

// apenas permite pular se estiver no chão ou em uma plataforma (velocidade_y == 0), a verificaçao de chao/plataforma vai ser adicionada no Jogador_atualizar
void Jogador_Pular(Jogador *jogador) {
    if (jogador->velocidade_y == 0) { 
        jogador->velocidade_y = FORCA_PULO; 
    }
}

//Esta função é chamada a cada ciclo do timer.
 * @param jogador Ponteiro para a struct Jogador.
 * @param plataformas O array de plataformas (necessário para verificação de colisão).

void Jogador_Atualizar(Jogador *jogador, Plataforma *plataformas) {
    // aplicando  a gravidade
    jogador->velocidade_y += GRAVIDADE;
    
    // atualizando a posição vertical
    jogador->y += jogador->velocidade_y;
    
    // aqui vai ser a verificação da plataforma (ainda será implementada, segue exemplo)
    
    // se cair abaixo do limite de jogo e chegou no inferno de diego
    if (jogador->y > MAXY) { 
        jogador->vidas--; // -1 vida
        // reinicia o jogador na base
        Jogador_Inicializar(jogador); 
    }
    
}


//desenha o jogador na tela 
void Jogador_Desenhar(Jogador *jogador) {
    // 1. Define a cor do jogador
    screenSetColor(WHITE, BLACK);
    
    // 2. Move o cursor para a posição do jogador
    screenGotoxy(jogador->x, jogador->y);
    
    // 3. Desenha o símbolo do jogador
    printf("%c", jogador->simbolo);
    
    // 4. Reseta a cor para o padrão (boa prática)
    screenSetNormal();
