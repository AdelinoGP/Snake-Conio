#define TAMANHO 24
#define TAMANHOMAX (TAMANHO + 1) * (TAMANHO + 1) * 4
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdint.h>

void hidecursor();
void delay(int milliseconds);

struct objeto
{
    int x,y;
};


int main()
{
    struct objeto cobras[200];
    struct objeto ponto;
    COORD coord;
    char mundo[(TAMANHO)][TAMANHO + 1];
    char buffer[(TAMANHOMAX)];
    char teclado;
    int cx;
    int cobrasize = 0;
    int dircobra = 0;
    int i,c;
    hidecursor();
    coord.X=0;
    coord.Y=0;
    srand (time(NULL));
    cobras[0].x = rand() % TAMANHO;
    cobras[0].y = rand() % TAMANHO;
    ponto.x = rand() % TAMANHO;
    ponto.y = rand() % TAMANHO;
    for (i=1; i<200; i++){
        cobras[i].x = 99;
        cobras[i].y = 99;
    }
    for(i=0; i<TAMANHO; i++)
    {
        for (c=0; c<TAMANHO; c++)
            mundo[i][c] = ' ';
    }
    while (1)
    {
        //limpa o sprite da cobra na matriz do mundo
        for (i = 0; i <= cobrasize; i++)
        {
            mundo[cobras[i].y][cobras[i].x]=' ';
        }
        //L� teclado e responde a input
        if(kbhit())
            teclado = getch();
        else
            teclado = 0;

        switch(teclado)
        {
            case 'w':dircobra = 0;  break;
            case 's':dircobra = 1;  break;
            case 'a':dircobra = 2;  break;
            case 'd':dircobra = 3;  break;
        }
        //Copia cobra anterior para posi��o da cobra da frente
        for (i = cobrasize; i > 0; i--)
        {
            cobras[i].y = cobras[i-1].y;
            cobras[i].x = cobras[i-1].x;
        }

        //Move Cobra[0]
        switch(dircobra)
        {
            case 0:cobras[0].y--;   break;
            case 1:cobras[0].y++;   break;
            case 2:cobras[0].x--;   break;
            case 3:cobras[0].x++;   break;
        }

        //Checa se fora do limite
        if(cobras[0].y > TAMANHO-1) cobras[0].y = 0;
        if(cobras[0].y < 0)         cobras[0].y = TAMANHO-1;
        if(cobras[0].x > TAMANHO-1) cobras[0].x = 0;
        if(cobras[0].x < 0)         cobras[0].x = TAMANHO-1;


        if(cobras[0].x == ponto.x && cobras[0].y == ponto.y)
        {
            ponto.x = rand() % TAMANHO;
            ponto.y = rand() % TAMANHO;
            cobrasize++;
        }
        for (i = 0; i < cobrasize; i++){
            for (c = 0; c < cobrasize; c++){
                if(cobras[i].x == cobras[c].x && cobras[i].y == cobras[c].y && c != i){
                    system("cls");
                    printf("GameOver\n");
                    delay(999999);
                }
            }
        }
        mundo[ponto.y][ponto.x] = 'X';
        for (i = 0; i <= cobrasize; i++)
        {
            mundo[cobras[i].y][cobras[i].x] = '0';
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
        cx = 0;
        for(i = 0; i < TAMANHO; i++)
        {
            for (c = 0; c < TAMANHO; c++){
                cx += snprintf(buffer + cx,TAMANHOMAX-cx,"%c ",mundo[i][c]);
            }
            cx += snprintf(buffer + cx,TAMANHOMAX-cx,"|\n");
        }
        puts (buffer);
        printf("Pontos = %d  Jogo por Adelino Penedo\n",cobrasize*5);
        delay(150);
    }
    return 0;
}

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
