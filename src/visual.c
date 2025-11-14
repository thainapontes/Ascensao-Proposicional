#include "visual.h"
#include "screen.h"
#include <stdio.h>

void Visual_DesenharGuilherme(int x, int y)
{

    screenSetColor(BLUE, BLACK);
    screenGotoxy(x, y);
    printf(" (o) ");
    screenGotoxy(x, y + 1);
    printf(" /_\\ ");
    screenGotoxy(x, y + 2);
    printf(" | | ");
    screenSetNormal();
}

void Visual_DesenharDiego(int x, int y)
{

    screenSetColor(RED, BLACK);

    screenGotoxy(x, y);
    printf(" \\^/ ");

    screenGotoxy(x, y + 1);
    printf(" (X) ");

    screenGotoxy(x, y + 2);
    printf("  Y  ");

    screenSetNormal();
}
