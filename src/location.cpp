#include "location.h"


location::location() {
	// start with no one occupying the cell and no neighbors
	IsOccupied = false;
}

location::location(bool Occupied) {
	IsOccupied = Occupied;
}

location::~location(){
	// Do nothing
}

bool location::getIsOccupied() {
	return IsOccupied;
}

void location::setIsOccupied(bool Occupied) {
	IsOccupied = Occupied;
}



void location::printLocation() {
	if (IsOccupied == true) {
		cout << 'X';
	}
	else {
		cout << '-';
	}
}



