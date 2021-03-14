#include "graphics.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdio>
#include <math.h>
#include "karel.h"
#include "wall.h"
#include "background.h"
#include "obdelnik.h"
#include "finish.h"
#include <list>
#include <vector>

#ifndef GAME_H
#define GAME_H

class Game
{
public:
    int width, height, x, y;
    bool quit, finish_init, pause;
    // počet zdí které se mají nakreslit

    // pole s pozicemi zdí a Karla
    std::vector<int> positions_x;
    std::vector<int> positions_y;

    // vytvoření listu zdí
    std::list<Wall *> walls;
    std::list<Wall *>::iterator w, w2;
    //vytovření listu obdelníčků
    std::list<Obdelnik *> obdelniky;
    std::list<Obdelnik *>::iterator o, o2;
    // vytvoření listu konců
    std::list<Finish *> finishes;
    std::list<Finish *>::iterator f, f2;

    std::list<Karel *> Karls;
    std::list<Karel *>::iterator k, k2;

    std::list<Background *> backgrounds;
    std::list<Background *>::iterator b, b2;

    Obrazovka *obrazovka = Obrazovka::instance();

    // vlajky na monitorování stisků kláves
    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };

    // stisky kláves
    SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
    SDL_Surface *KeySurface = NULL;
    SDL_Event event;

    Game(int z);
    void kresli();
    void init(const int limit);
    void move();
    void turn();
    void place(int r, int g, int b);
    bool wall = false;
    bool end = false;
    int limit = 0;
};

#endif // GAME_H