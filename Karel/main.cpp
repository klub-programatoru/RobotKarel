#include "graphics.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdio>
#include <math.h>
#include "karel.h"
#include "wall.h"
#include "background.h"
#include "karel.h"
#include "obdelnik.h"
#include "finish.h"
#include "game.h"
#include <list>
#include <vector>
#include <string>
#include <iostream>

int z = 159;
int delay_s = 1500;
int delay_m = 750;
int delay_p = 250;
Game game(z);
Karel karel(game.x, game.y, game.width, game.height);

#define zed game.wall
#define hranice game.end
#define zadan 0
#define jednoducha 15
#define strdni 50
#define tezka 75
#define BILA 255, 255, 255
#define CERNA 0, 0, 0
#define CERVENA 255, 0, 0
#define ZELENA 0, 255, 0
#define MODRA 0, 0, 255

void start(int obtiznost)
{
    game.init(obtiznost);
    game.kresli();
    SDL_Delay(delay_s);
}

void end()
{
    while (!game.quit)
    {
        game.kresli();

        // hlídání kláves
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                // ESCAPE = KONEC
                case SDLK_ESCAPE:
                    game.obrazovka->zavri();
                    game.quit = true;
                    return;
                    // ŠIPKA DOLŮ = POHYB
                    // case SDLK_DOWN:
                    //     (*game.k)->move();
                    //     break;
                    // // ŠIPKA DOLEVA = OTOČKA
                    // case SDLK_LEFT:
                    //     (*game.k)->turn();
                    //     break;
                    // // MEZERNIK
                    // case SDLK_SPACE:
                    //     game.obdelniky.push_back(new Obdelnik(10, 10, 10, (*game.k)->x, (*game.k)->y, game.width / 12, game.height / 12));
                }
                break;
            }
        }
    }
    game.obrazovka->zavri();
}

void krok()
{
    game.kresli();
    SDL_Delay(delay_m);
    game.move();
    game.kresli();

    // hlídání kláves
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                delay_s = 0;
                delay_m = 0;
                delay_p = 0;
                return;
            }
            break;
        }
    }
}

void otoc()
{
    game.kresli();
    SDL_Delay(delay_m);
    game.turn();
    game.kresli();
}

void poloz(int r, int g, int b)
{
    game.kresli();
    SDL_Delay(delay_p);
    game.place(r, g, b);
    game.kresli();
}

#define krok krok()
#define otoc otoc()

//MAIN LOOP
int main(int arg, char *argv[])
{
    start(0);
    /* Tady je prostor pro vaš příkazy:*/

    //krok;
    //otoc;
    //poloz(BILA);

    /* Konce prostoru pro příkazy!*/
    end();
    return 1;
}