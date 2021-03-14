
#include "graphics.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include "karel.h"
#include <string>

Karel::Karel(float sx, float sy, int w, int h)
{
    // šířka a výška obrazovky
    this->w = w;
    this->h = h;
    // startovní pozice Karla
    this->x = sx;
    this->y = sy;
    // načtení obrázků karla
    karel_down.nacti("Karel_down.png");
    karel_up.nacti("Karel_up.png");
    karel_left.nacti("Karel_left.png");
    karel_right.nacti("Karel_right.png");
    // uložení šířky a výšky karla
    width = w / 12;
    height = h / 12;
}

void Karel::move()
{

    // POHYB VE SPRÁVNÉM SMĚRU
    // dolů
    if (directions[n] == 0)
    {
        this->x = x;
        this->y += height;
        karel_down.umisti(x, y);
    }
    // doprava
    else if (directions[n] == 1)
    {
        this->x += width;
        this->y = y;
        karel_right.umisti(x, y);
    }
    //nahoru
    else if (directions[n] == 2)
    {
        this->x = x;
        this->y -= height;

        karel_up.umisti(x, y);
    }
    //doleva
    else if (directions[n] == 3)
    {
        this->x -= width;
        this->y = y;
        karel_left.umisti(x, y);
    }
    //rovně
    else
    {
        this->x = x;
        this->y += height;
        karel_down.umisti(x, y);
    }

    //MEZE ORAZOVKY
    if (x > w - karel_left.w)
    {
        printf("Narzil jste!");
        obrazovka->zavri();
    }
    if (y > h - karel_left.h)
    {
        printf("Narzil jste!");
        obrazovka->zavri();
    }
    if (x < 0 + karel_left.w)
    {
        printf("Narzil jste!");
        obrazovka->zavri();
    }
    if (y < 0 + karel_left.h)
    {
        printf("Narzil jste!");
        obrazovka->zavri();
    }

    // vypisování Karlovy pozice
    /*printf("%d\n", x);
    printf("%d\n", y);*/
}

void Karel::draw()
{
    // NAKRESLENÍ KARLA OTOČENÉHO VE SPRÁVNÉM SMĚRU
    // nahoru
    if (directions[n] == 0)
    {
        karel_down.umisti(x, y);
        karel_down.kresli();
    }
    // doprava
    else if (directions[n] == 1)
    {
        karel_right.umisti(x, y);
        karel_right.kresli();
    }
    // nahoru
    else if (directions[n] == 2)
    {
        karel_up.umisti(x, y);
        karel_up.kresli();
    }
    // doleva
    else if (directions[n] == 3)
    {
        karel_left.umisti(x, y);
        karel_left.kresli();
    }
    //nahoru
    else
    {
        karel_down.umisti(x, y);
        karel_down.kresli();
    }
}

void Karel::turn()
{
    // ZMĚNA INDEXU POLE URČUJÍCÍHO SMĚR POHYBU
    if (n <= 2)
    {
        n += 1;
    }
    else
    {
        n = 0;
    }
}
