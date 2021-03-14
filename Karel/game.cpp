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
#include "game.h"

using namespace std;

#define BILA 255, 255, 255

Game::Game(int z)
{
    positions_x.clear();
    positions_y.clear();
    // šířka a výška obrazovky
    width = 66 * 12;
    height = 66 * 12;

    // vlajka signalizující koncec programu
    quit = false;

    // statrovní pozcie karla
    x = 0;
    y = 0;

    // vlajka začátku kreslení konce
    finish_init = true;
    // vlajka pauzy programu
    pause = false;
}

void Game::init(const int limit)
{
    this->limit = limit;
    // vytvoření obrazovky
    obrazovka->inicializuj("Robot Karel", width, height, SDL_WINDOW_SHOWN);

    // hlídání stisků kláves ?
    KeySurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

    // vytvoření karla a pozadí
    Background back(width, height);

    if (limit >= 0)
    {
        // vytvoření jednotlivých zdí
        for (int i = 0; i < limit; i++)
        {
            Wall *wall = new Wall(0, 0);
            walls.push_back(wall);
        }
    }
    else if (limit == -1)
    {
    }
    else if (limit == -2)
    {
        int random = rand() % 9;
        while (random == 0)
        {
            int random = rand() % 9;
        }
        int random_2 = rand() % 11;
        for (int i = 0; i < width - 1; i = i + 66)
        {
            if (i == random_2 * 66)
            {
            }
            else
            {
                walls.push_back(new Wall(i, 66 * random));
            }
        }
        for (int i = 0; i < random; i++)
        {

            positions_y.push_back(i * 66);
        }
        positions_y.push_back(66 * random);
    }
    //přidání nového obdelníku do listu
    //obdelniky.push_back(new Obdelnik(BILA, karel.x, karel.y, width/12, height/12));

    Karls.push_back(new Karel(x, y, width, height));

    backgrounds.push_back(new Background(width, height));

    // přidání počáteční pozice karla
    positions_x.push_back(x);
    positions_y.push_back(y);
}

void Game::kresli()
{
    // Karel karel(x, y, width, height);
    //kreslení pozadí
    for (b = backgrounds.begin(); b != backgrounds.end(); b++)
    {
        (*b)->draw();
    }
    k = Karls.begin();

    wall = false;

    if (limit != -1)
    {
        // kreslení zdí z listu a hlídání kolize s Karlem
        for (w = walls.begin(); w != walls.end(); w++)
        {
            //KRESLENÍ
            (*w)->draw();

            // přidání pozic zdí
            positions_x.push_back((*w)->x);
            positions_y.push_back((*w)->y);

            // inicializace konce
            if (finish_init)
            {
                finishes.push_back(new Finish(positions_x, positions_y));
                finish_init = false;
            }

            //KOLIZE
            if ((*k)->x + 33 > (*w)->x && (*k)->y + 33 > (*w)->y && (*k)->x + 33 < (*w)->x + 66 && (*k)->y + 33 < (*w)->y + 66)
            {
                printf("1: %i > %i     &&  %i > %i     &&  %i < %i     &&  %i < %i     &&  %i == 0\n", (*k)->x + 33, (*w)->x, (*k)->y + 99, (*w)->y, (*k)->x + 33, (*w)->x + 66, (*k)->y + 99, (*w)->y + 66, (*k)->n);
                printf("2: %i > %i     &&  %i > %i     &&  %i < %i     &&  %i < %i     &&  %i == 1\n", (*k)->x + 99, (*w)->x, (*k)->y + 33, (*w)->y, (*k)->x + 99, (*w)->x + 66, (*k)->y + 33, (*w)->y + 66, (*k)->n);
                printf("3: %i > %i     &&  %i > %i     &&  %i < %i     &&  %i < %i     &&  %i == 2\n", (*k)->x - 33, (*w)->x, (*k)->y - 99, (*w)->y, (*k)->x - 33, (*w)->x + 66, (*k)->y - 99, (*w)->y + 66, (*k)->n);
                printf("4: %i > %i     &&  %i > %i     &&  %i < %i     &&  %i < %i     &&  %i == 3\n", (*k)->x - 99, (*w)->x, (*k)->y - 33, (*w)->y, (*k)->x - 99, (*w)->x + 66, (*k)->y - 33, (*w)->y + 66, (*k)->n);
                printf("Karel narazil!");
                obrazovka->zavri();
            }

            //under
            if ((*k)->x + 33 > (*w)->x && (*k)->y + 99 > (*w)->y && (*k)->x + 33 < (*w)->x + 66 && (*k)->y + 99 < (*w)->y + 66 && (*k)->n == 0)
            {
                wall = true;
            }
            //right
            else if ((*k)->x + 99 > (*w)->x && (*k)->y + 33 > (*w)->y && (*k)->x + 99 < (*w)->x + 66 && (*k)->y + 33 < (*w)->y + 66 && (*k)->n == 1)
            {
                wall = true;
            }
            //above
            else if ((*k)->x + 33 > (*w)->x && (*k)->y - 99 < (*w)->y + 66 && (*k)->x + 33 < (*w)->x + 66 && (*k)->y - 99 > (*w)->y && (*k)->n == 2)
            {
                wall = true;
            }
            else if ((*k)->x - 99 < (*w)->x + 66 && (*k)->y + 33 > (*w)->y && (*k)->x - 99 > (*w)->x && (*k)->y + 33 < (*w)->y + 66 && (*k)->n == 3)
            {
                wall = true;
            }
        }
    }

    end = false;

    //under
    if ((*k)->x + 99 > width && (*k)->n == 1)
    {
        end = true;
    }
    //right
    else if ((*k)->x - 33 < 0 && (*k)->n == 3)
    {
        end = true;
    }
    //above
    else if ((*k)->y + 99 > height && (*k)->n == 0)
    {
        end = true;
    }
    else if ((*k)->y - 33 < 0 && (*k)->n == 2)
    {
        end = true;
    }

    // kreslení konce
    for (f = finishes.begin(); f != finishes.end(); f++)
    {
        // kreslení konce
        (*f)->draw();
        pause = false;
        // kolize s koncem
        if ((*k)->x + 33 > (*f)->x && (*k)->y + 33 > (*f)->y && (*k)->x + 33 < (*f)->x + 66 && (*k)->y + 33 < (*f)->y + 66)
        {
            pause = true;
            printf("****!Vítězství!****");
        }
    }

    // procházení listu obdelníků a jejich kreslení
    for (o = obdelniky.begin(); o != obdelniky.end(); o++)
    {
        (*o)->draw();
    }

    (*k)->draw();

    //aktualizace obrazovky
    obrazovka->aktualizuj();

    while (pause)
    {
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
                    obrazovka->zavri();
                    quit = true;
                    return;
                }
                break;
            }
        }
    }
}

void Game::move()
{
    (*k)->move();
}

void Game::turn()
{
    (*k)->turn();
}

void Game::place(int r, int g, int b)
{
    obdelniky.push_back(new Obdelnik(r, g, b, (*k)->x, (*k)->y, width / 12, height / 12));
}