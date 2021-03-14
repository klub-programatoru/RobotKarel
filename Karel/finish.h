#ifndef FINISH_H
#define FINISH_H
#include "graphics.h"
#include <string>
#include <vector>

using namespace std;

class Finish
{
public:
    int n, m, x, y = 0;
    Obrazek finish;
    Obrazovka* obrazovka = Obrazovka::instance();

    Finish( std::vector<int> posx, std::vector<int> posy );

    void draw();
};
#endif // FINISH_H