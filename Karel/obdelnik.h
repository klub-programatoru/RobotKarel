#ifndef OBDELNIK_H
#define OBDELNIK_H

#include "graphics.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

class Obdelnik
{
public:
    Obrazovka* obrazovka = Obrazovka::instance();
    // vnitřní proměnné
    int r, g, b, x, y, width, height = 0;
    
    Obdelnik(int r, int g, int b, int x, int y, int width, int height);

    void draw();

};

#endif // OBDELNIK_H
