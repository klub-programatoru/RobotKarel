#ifndef WALL_H
#define WALL_H
#include <string>
#include "graphics.h"

class Wall
{
public:
    int x, y, w, h, n, m;
    Obrazek zed;
    Obrazovka *obrazovka = Obrazovka::instance();

    Wall(int a, int b);

    void draw();
};

#endif // WALL_H