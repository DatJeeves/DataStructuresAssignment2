#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>

using namespace std;
class location {

public:
    location();
    location(bool isOccupied);
    ~location();

    bool getIsOccupied();
    void setIsOccupied(bool Occupied);

    void printLocation();

private:
    bool IsOccupied;

};

#endif
