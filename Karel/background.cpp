
#include "graphics.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include "background.h"

Background::Background(int w, int h)
{
    this->w = w;
    this->h = h;
}

void Background::draw()
{
    barva(0, 133, 73);
    obdelnik(0, 0, w, h);


    barva(150, 150, 150);
    float r_width = w/12;
    float rect_width = r_width;

    for(int g = 1; g < 13; g++)
    {
        int sx = rect_width;
        int kx = rect_width;
        cara(sx, 0, kx, h);
        rect_width = g*r_width;
    }

    float r_height = h/12;
    float rect_height = r_height;

    for(int e = 1; e < 13; e++)
    {
        int sy = rect_height;
        int ky = rect_height;
        cara(0, sy, w, ky);
        rect_height = e*r_height;
    }
}