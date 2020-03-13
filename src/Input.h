#ifndef INPUT_H
#define INPUT_H

#include <iostream>

using namespace std;
class Input {
public:
    Input();
    ~Input();

    void GetConfiguration();
    string GetFilename();

  

    //Variables
    bool IsPreconfigWorld;
    string PreconfigFileName;
    string OutputFileName;
    int GridHeight;
    int GridWidth;
    float Density;
    int GameMode;
    int OutputMode;

private:
    void GetHeight();
    void GetWidth();
    void GetDensity();
    void GetBoundryMode();
    void GetGenerationOutputOption();
};

#endif
