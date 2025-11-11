#include <stdio.h>
#include <stdlib.h>
#include "screen.h" 
#include "keyboard.h" 
#include "timer.h" 
#include "visual.h"

int main() {
    
    Jogador meu_jogador;
    char simbolo_escolhido;

    // FASE 1: Coleta de Dados (Antes de inicializar o modo gráfico)
    printf("--- BEM-VINDO(A) A POUPROSIÇÕES ---\n");
    printf(" Voc
    printf("Digite o caractere que irá representar seu Jogador (ex: @, P, J): ");
    
    // Lê o caractere escolhido pelo usuário
    if (scanf(" %c", &simbolo_escolhido) != 1) {
        simbolo_escolhido = '@'; // Fallback: usa '@' se a leitura falhar
    }

    // ----------------------------------------------------
    // FASE 2: Inicialização do Jogo e do Modo Gráfico
    // ----------------------------------------------------
    
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
            
            // Dentro do main.c, quando a pergunta aparece:
            Visual_DesenharGuilherme(5, 5); // Desenha o ícone no canto superior esquerdo
            
            // Dentro do loop de desenho:
            Visual_DesenharDiego(SCRENDX - 7, SCRENDY - 3); // Desenha o ícone no canto inferior direito
        }

        // CONDIÇÃO DE FIM DE JOGO VIRÁ AQUI
    }

    //FINALIZAÇÃO
    keyboardDestroy();
    screenDestroy();
    
    return 0;
}
