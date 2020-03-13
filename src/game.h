#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include "grid.h"
#include "Input.h"

using namespace std;
class Game{
  public:
    Game();
    ~Game();

    void start();
    
  private:
    //local variables for the class

    Grid* currentGrid;
    Grid* futureGrid;

    Grid* g1;
    Grid* g2;

    void round(int generation, int GameMode);


};
#endif
