#include "visual.h"
#include "screen.h"
#include <stdio.h>


void Visual_DesenharGuilherme(int x, int y) {
    
    screenSetColor(BLUE, BLACK);
    
    // aréola  (simulada) de guilherme
    screenGotoxy(x, y);
    printf(" (o) "); 

    // corpo de guilherme
    screenGotoxy(x, y + 1);
    printf(" /_\\ ");

    // base do corpo, asas etc
    screenGotoxy(x, y + 2);
    printf(" | | ");

    screenSetNormal(); // Reseta as cores
}


void Visual_DesenharDiego(int x, int y) {
    
    screenSetColor(RED, BLACK);

    //  Chifres e Olhos
    screenGotoxy(x, y);
    printf(" \\^/ "); 

    // Rosto/Corpo
    screenGotoxy(x, y + 1);
    printf(" (X) ");

    //  Tridente
    screenGotoxy(x, y + 2);
    printf("  Y  ");

    screenSetNormal(); // Reseta as cores
}
