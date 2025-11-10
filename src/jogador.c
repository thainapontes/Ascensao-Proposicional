#include "jogador.h"
#include "screen.h" // necessário para usar as constantes de tela (SCRSTARTX, SCRENDY, etc.)

//Inicializa a struct do jogador com valores de início de jogo

void Jogador_Inicializar(Jogador *jogador) {
    //posição na tela, onde o jogador deve começar a aparecer
    int centro_x = SCRSTARTX + (SCRENDX - SCRSTARTX) / 2;
    
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

// ... Outras funções (Jogador_MoverHorizontal, etc.) virão aqui.
