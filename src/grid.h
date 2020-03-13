#ifndef READER_H
#define READER_H
#include <iostream>
#include <fstream>
#include "location.h"
#include "Input.h"

using namespace std;
class Grid{
  public:   
    int my_height;
    int my_width;
    int my_mode;

    Grid(int height, int width, float density);
    Grid(string file);
    ~Grid();

    void displayGrid();
    bool IsOccupied(int row, int col);
    void SetOccupied(int row, int col);
    void ClearOccupied(int row, int col);
    int  CheckNextState(int row, int col, int GameMode);
    bool IsGridSame(Grid* newGrid);

  private:
    //local variables for the class
    location** GridPtr;

    void initGrid(float density); 
    float getRandomNumber();

};
#endif
