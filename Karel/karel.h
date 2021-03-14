#ifndef KAREL_H
#define KAREL_H
#include <string>
#include "graphics.h"

class Karel
{
public:
    // Karlovy pozice
    int x = 0;
    int y = 0;
    // šiřka a výska obrazovky
    int w = 0;
    int h = 0;
    // index pole směru pohybu
    int n = 0;
    // šířka a výška Karla
    int width, height = 0;
    // počáteční pozice Karla
    float sx, sy;
    // pole určující směr pohybu Karla
    int directions[4] = {0, 1, 2, 3};
    
    // obrázky Karla
    Obrazek karel_down;
    Obrazek karel_up;
    Obrazek karel_right;
    Obrazek karel_left;
    // OBRAZOVKA
    Obrazovka* obrazovka = Obrazovka::instance();
    
    Karel(float sx, float sy, int w, int h);

    void draw();
    void move();
    void turn();
};


#endif // KAREL_H