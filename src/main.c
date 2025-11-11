#include <stdio.h>
#include <stdlib.h>
#include "screen.h" 
#include "keyboard.h" 
#include "timer.h" 
#include "visual.h"

int main() {
    screenInit(1); // inicializar a tela e desenha as bordas
    keyboardInit(); // configura ro teclado para leitura inst
    timerInit(50); // inicializar o timer 
    
    //escreve o totulo do jogo no topo 
    screenSetColor(YELLOW, BLACK);
    screenGotoxy(SCRSTARTX, SCRSTARTY);
    printf("PouProsições, A ascensão Proposicional");
    screenSetNormal();

    // LOOP PRINCIPAL 
    // aq vai rodar a mecânica do jogo: mover aluno, verificar colisão, etc.
    while (1) {
        // Leitura de Entrada (Teclado)
        if (keyhit()) {
            char key = readch();
            if (key == 'q') 
              break; // sai do loop ao apertar 'q'
            // fazer dps a lógica de movimento: se apertar 'a' ou 'd' (esquerda/direita), move o aluno etc
        }

        // Lógica de Tempo e Atualização (Gravidade, Movimento de Plataformas)
        if (timerTimeOver()) {
            // Lógica para mover o aluno para baixo (Gravidade)
            // Lógica para desenhar/atualizar o estado da tela (screenUpdate)
        }

        // CONDIÇÃO DE FIM DE JOGO VIRÁ AQUI
    }

    //FINALIZAÇÃO
    keyboardDestroy();
    screenDestroy();
    
    return 0;
}
