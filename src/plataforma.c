#include <stdio.h>
#include <stdlib.h>     // Para rand() e srand() (usamos rand() para definir a posição e o tipo da plataforma, ela gera numeros pseudoaleatórios)
#include <time.h>       //usamos srand usada para inicializar o gerador de números pseudoaleatórios. Ela define o ponto de partida (a semente) para a sequência que a função rand() irá gerar.)
#include "plataforma.h"
#include "screen.h"     // Para desenho (screenGotoxy, screenSetColor)
#include "jogador.h"    // Para a struct Jogador (necessário na Colisao)

static int semente_inicializada = 0; // Flag estática
static void inicializar_semente() {
    if (!semente_inicializada) {
        srand(time(NULL));//para garantir que as plataformas geradas sejam diferentes a cada vez que o programa é executado
        semente_inicializada = 1;
    }
}

void Plataforma_GerarNova(Plataforma *p, int y_inicial) {
    inicializar_semente();

    // 1. Posição e Dimensão
    p->x = SCRSTARTX + (rand() % (SCRENDX - SCRSTARTX - 5)); 
    p->y = y_inicial;
    p->largura = 8 + (rand() % 5); 

    // 2. Tipo da Plataforma (com chance de ser especial)
    int chance = rand() % 100;
    
    if (chance < 80) {
        p->tipo = NORMAL; // 80% de chance
    } else if (chance < 90) {
        p->tipo = PERGUNTA; // 10% de chance
    } else {
        p->tipo = QUEBRAVEL; // 10% de chance
    }
    
    p->usada = 0; // Estado inicial (não usada)
}

/**
 * Desenha a plataforma na tela usando cores e caracteres BOX.
 * @param p Ponteiro para a struct Plataforma.
 */
void Plataforma_Desenhar(Plataforma *p) {
    // Se a plataforma for quebrável e já tiver sido usada, não a desenha.
    // Isso simula a quebra da plataforma.
    if (p->tipo == QUEBRAVEL && p->usada == 1) {
        return; 
    }
    
    char caractere = BOX_HLINE;
    screenColor cor = GREEN;
    
    // 1. Define a cor e o símbolo (com base no ENUM)
    switch (p->tipo) {
        case NORMAL:
            cor = GREEN;
            caractere = BOX_HLINE; // Linha horizontal da CLI-lib
            break;
        case PERGUNTA:
            cor = BLUE; // Plataforma de pergunta lógica
            caractere = '?';
            break;
        case QUEBRAVEL:
            cor = LIGHTGRAY; // Plataforma quebrável (cinza/frágil)
            caractere = BOX_DIAMOND; // Símbolo de diamante
            break;
        case PROP_LOGICA:
            cor = YELLOW; // Plataforma de proposição (P ou Q)
            caractere = BOX_BLOCK; // Bloco sólido
            break;
    }

    screenSetColor(cor, BLACK);
    screenBoxEnable(); // Habilita o modo de desenho de caixas

    // 2. Desenha a linha da plataforma
    for (int i = 0; i < p->largura; i++) {
        screenGotoxy(p->x + i, p->y);
        
        // Se for uma plataforma de pergunta, só o centro deve ter o '?'
        if (p->tipo == PERGUNTA && i != p->largura / 2) {
             printf("%c", BOX_HLINE);
        } else {
             printf("%c", caractere);
        }
    }
    
    screenBoxDisable(); // Desabilita o modo de desenho de caixas
    screenSetNormal(); // Reseta as cores
}

int Plataforma_VerificarColisao(Jogador *jogador, Plataforma *p) {
    // 1. Verifica se o jogador está na mesma linha vertical que a plataforma
    if (jogador->y != p->y) {
        return 0; // Sem colisão vertical
    }

    // 2. Verifica se a colisão é POR CIMA (se o jogador estava caindo)
    if (jogador->velocidade_y < 0) {
        return 0; // Está subindo, não pode pousar
    }

    // 3. Verifica se o jogador está horizontalmente SOBRE a plataforma
    if (jogador->x >= p->x && jogador->x < (p->x + p->largura)) {
        
        if (p->tipo == QUEBRAVEL) {
            p->usada = 1; // Manda o flag para ser removida/quebrada
        }
        
        return 1; // Colisão detectada!
    }

    return 0;
}
