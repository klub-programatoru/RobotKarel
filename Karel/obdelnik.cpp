#include "graphics.h"
#include "obdelnik.h"
#include <SDL2/SDL.h>
#include <stdio.h>

Obdelnik::Obdelnik(int r, int g, int b, int x, int y, int width, int height)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Obdelnik::draw()
{
    barva(r, g, b);
    obdelnik(x, y, x + width, y + height);
}