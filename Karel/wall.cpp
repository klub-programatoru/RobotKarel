
#include "graphics.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include "wall.h"
#include "karel.h"
#include <string>
#include <random>

Wall::Wall(int a = 0, int b = 0)
{
    // načtení obrázku zdi
    zed.nacti("Wall.jpg");

    if (a == 0 && b == 0)
    {
        // zvolení háhodného čísla od 0 do jedenácti
        n = rand() % 11;
        m = rand() % 11;
        while (n == 0 && m == 0 || m == 1 && n == 0 || m == 0 && n == 1 || m == 1 && n == 1)
        {
            n = rand() % 11;
            m = rand() % 11;
            printf("x: %i, y: %i \n", n, m);
        }
        // umístění zdi na souřadnice náhodného násobku 66
        x = n * 66;
        y = m * 66;
    }
    else
    {
        x = a;
        y = b;
    }

    zed.umisti(x, y);
}

void Wall::draw()
{
    // nakreslení zdi
    zed.kresli();
}