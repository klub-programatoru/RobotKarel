#include "graphics.h"
#include "finish.h"
#include "game.h"
#include <vector>

using namespace std;

extern Game game;

Finish::Finish(std::vector<int> posx, std::vector<int> posy)
{
    // načtení obrázku konce
    finish.nacti("finish.jpg");
    // zvolení háhodného čísla od 0 do jedenácti
    n = rand() % 11;
    m = rand() % 11;
    // umístění konce na souřadnice náhodného násobku 66
    x = n * 66;
    y = m * 66;

    // projde všechny pozice zdí a pokud se pozice konce nachází na pozici
    // zdi, změní pozici konce.
    for (int i = 0; i < game.positions_x.size(); i++)
    {
        while (x == game.positions_x[i])
        {
            n = rand() % 11;
            x = n * 66;
        }
    }
    for (int j = 0; j < game.positions_y.size(); j++)
    {
        while (y == game.positions_y[j])
        {
            m = rand() % 11;
            y = m * 66;
        }
    }

    finish.umisti(x, y);
    if (y < 6 * 66)
    {
        int a = 1;
    }
}

void Finish::draw()
{
    finish.kresli();
}