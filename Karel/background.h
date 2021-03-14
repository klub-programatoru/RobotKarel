#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <string>
#include "graphics.h"

class Background
{
public:
    int w, h;
    Background(int w, int h);

    void draw();
};

#endif // BACKGROUND_H