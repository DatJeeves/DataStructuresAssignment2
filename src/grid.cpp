#include "grid.h"
#include <cstdlib>
#include <fstream>
#include <random>


using namespace std;
//constructor class
Grid::Grid(int height, int width, float density){
    // This constructor will create a grid based on the given height and width
    // Since the values of the height and width are dynamic I need to use pointers 
    // for the creation
    my_height = height;
    my_width = width;

    // Make current grid pointer, point to an array of pointers
    GridPtr = new location*[my_width]; // row of pointers of location type

    for(int i = 0; i< my_width; ++i){
        GridPtr[i] = new location[my_height]; // points to an array of locations by height
    }
    
    initGrid(density);

}

Grid::Grid(string file){
    // This constructor will create a grid based on a previously created gird.
    // The predefined grid is located in the input file.
    ifstream stream;
    stream.open(file, ios::in);

    if(!stream){
        cout << "The file " << file << " had an issue." << endl;
        cout<< "File Stream is not good, please check the file and try again."<<endl;
        exit(1);
    }
  
    //obtained from: https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c
    else if(stream.peek() == std::ifstream::traits_type::eof()){
        cout<<"Your file "<<file<<" is empty, please enter a valid file."<<endl;
        exit(1);
    }
    string line;

    //Gets my_heights int value
    //need to change line var?
    stream >> my_height;
    stream >> my_width;

    //creation of the grid
    GridPtr = new location*[my_width];

    // For each row assign the values from the file
    for(int i = 0; i<my_height; ++i){
        GridPtr[i] = new location[my_width]; 
        stream >> line; // reads all the cells for that row in to a line

        // Assign the values based on the char in that line string
        for (int j = 0; j < my_width; ++j) {
            if (line[j] == 'X') {
                location cell(true);
                (GridPtr[i])[j] = cell;
            }
            else {
                location cell(false);
                (GridPtr[i])[j] = cell;
            }
        }
    }

}

Grid::~Grid(){
  for(int i = 0; i<my_height; ++i){
    delete[] GridPtr[i];
  } 
}


void Grid::displayGrid() {
    for (int i = 0; i < my_height; ++i) {
        for (int j = 0; j < my_width; ++j) {
            (GridPtr[i][j]).printLocation();
        }
        cout << endl;
    }
}

bool Grid::IsOccupied(int row, int col) {
    if ((GridPtr[row])[col].getIsOccupied()) {
        return true;
    }

    return false;
}

void Grid::SetOccupied(int row, int col) {
    (GridPtr[row])[col].setIsOccupied(true);

}

void Grid::ClearOccupied(int row, int col) {
    (GridPtr[row])[col].setIsOccupied(false);

}

int  Grid::CheckNextState(int row, int col, int GameMode) {
    int neighbors = 0;

    //Top row
    if (row == 0) {     
        if (col == 0) {
            //Top left corner
            if (GameMode == 1) {
                // doughnut mode with wrap around
                if (IsOccupied(my_height-1, my_width-1)) {
                    ++neighbors;
                }
                if (IsOccupied(my_height - 1, col)) {
                    ++neighbors;
                }
                if (IsOccupied(row, my_width - 1)) {
                    ++neighbors;
                }
                if (IsOccupied(my_height - 1, col+1)) {
                    ++neighbors;
                }
                if (IsOccupied(row+1, my_width - 1)) {
                    ++neighbors;
                }
            }
            else if (GameMode == 2) {
                // since we have a mirror image and its a corner
                // increment by three if occupied
                if (IsOccupied(row, col)) {
                    neighbors += 3;
                }
            }
            if (IsOccupied(row, col + 1)) {
                ++neighbors;
                if (GameMode == 2) {
                    // since we have a mirror image we can increment it again
                    ++neighbors;
                }
            }
            if (IsOccupied(row+1, col)) {
                ++neighbors;
                if (GameMode == 2) {
                    // since we have a mirror image we can increment it again
                    ++neighbors;
                }
            }
            if (IsOccupied(row + 1, col+1)) {
                ++neighbors;
            }
        }
        else if (col == (my_width-1)){
            //Top right corner
            if (GameMode == 1) {
                // doughnut mode with wrap around
                if (IsOccupied(my_height - 1, 0)) {
                    ++neighbors;
                }
                if (IsOccupied(row, 0)) {
                    ++neighbors;
                }
                if (IsOccupied(row+1, 0)) {
                    ++neighbors;
                }
                if (IsOccupied(my_height - 1, col)) {
                    ++neighbors;
                }
                if (IsOccupied(my_height-1, col-1)) {
                    ++neighbors;
                }
            }
            if (GameMode == 2) {
                // since we have a mirror image and its a corner
                // increment by three if occupied
                if (IsOccupied(row, col)) {
                    neighbors += 3;
                }
            }
            if (IsOccupied(row, col - 1)) {
                ++neighbors;     
                if (GameMode == 2) {
                    // since we have a mirror image we can increment it again
                    ++neighbors;
                }
            }
            if (IsOccupied(row + 1, col)) {
                ++neighbors;
                if (GameMode == 2) {
                    // since we have a mirror image we can increment it again
                    ++neighbors;
                }
            }
            if (IsOccupied(row + 1, col - 1)) {
                ++neighbors;
                
            }
        
        }
        else {
            if (GameMode == 1) {
                // doughnut mode with wrap around
                if (IsOccupied(my_height - 1, col-1)) {
                    ++neighbors;
                }
                if (IsOccupied(my_height - 1, col)) {
                    ++neighbors;
                }
                if (IsOccupied(my_height - 1, col+1)) {
                    ++neighbors;
                }
            }
            if (GameMode == 2) {
                if (IsOccupied(row, col)) {
                    // Add its own reflection
                    ++neighbors;
                }
            }
            if (IsOccupied(row, col + 1)) {
                ++neighbors;
                if (GameMode == 2) {
                    // since we have a mirror image on top
                    // increment again
                    ++neighbors;
                }
            }
            if (IsOccupied(row + 1, col+1)) {
                ++neighbors;
            }
            if (IsOccupied(row, col - 1)) {
                ++neighbors;
                if (GameMode == 2) {
                    // since we have a mirror image on top
                    // increment again
                    ++neighbors;
                }
            }
            if (IsOccupied(row + 1, col)) {
                ++neighbors;
            }
            if (IsOccupied(row + 1, col - 1)) {
                ++neighbors;
            }
        }
    }

    // bottom row
    if (row == (my_height - 1)) {
        if (col == 0) {
            // Bottom left corner
            if (GameMode == 1) {
                // doughnut mode with wrap around
                if (IsOccupied(0, my_width - 1)) {
                    ++neighbors;
                }
                if (IsOccupied(0, col)) {
                    ++neighbors;
                }
                if (IsOccupied(row, my_width - 1)) {
                    ++neighbors;
                }
                if (IsOccupied(0, col + 1)) {
                    ++neighbors;
                }
                if (IsOccupied(row-1, my_width - 1)) {
                    ++neighbors;
                }
            }
            if (GameMode == 2) {
                // since we have a mirror image and its a corner
                // increment by three if occupied
                if (IsOccupied(row, col)) {
                    neighbors += 3;
                }
            }
            if (IsOccupied(row, col + 1)) {
                ++neighbors;
                if (GameMode == 2) {
                    // since we have a mirror image we can increment it again
                    ++neighbors;
                }
            }
            if (IsOccupied(row - 1, col)) {
                ++neighbors;
                if (GameMode == 2) {
                    // since we have a mirror image we can increment it again
                    ++neighbors;
                }
            }
            if (IsOccupied(row - 1, col + 1)) {
                ++neighbors;
            }
        }
        else if (col == (my_width - 1)) {
            // Bottom right corner
            if (GameMode == 1) {
                // doughnut mode with wrap around
                if (IsOccupied(0, 0)) {
                    ++neighbors;
                }
                if (IsOccupied(0, col)) {
                    ++neighbors;
                }
                if (IsOccupied(0, col-1)) {
                    ++neighbors;
                }
                if (IsOccupied(row, 0)) {
                    ++neighbors;
                }
                if (IsOccupied(row-1, 0)) {
                    ++neighbors;
                }
            }
            if (GameMode == 2) {
                // since we have a mirror image and its a corner
                // increment by three if occupied
                if (IsOccupied(row, col)) {
                    neighbors += 3;
                }
            }
            if (IsOccupied(row, col - 1)) {
                ++neighbors;
                if (GameMode == 2) {
                    // since we have a mirror image we can increment it again
                    ++neighbors;
                }
            }
            if (IsOccupied(row - 1, col)) {
                ++neighbors;
                if (GameMode == 2) {
                    // since we have a mirror image we can increment it again
                    ++neighbors;
                }
            }
            if (IsOccupied(row - 1, col - 1)) {
                ++neighbors;
            }

        }
        else {
            if (GameMode == 1) {
                // doughnut mode with wrap around
                if (IsOccupied(0, col - 1)) {
                    ++neighbors;
                }
                if (IsOccupied(0, col)) {
                    ++neighbors;
                }
                if (IsOccupied(0, col + 1)) {
                    ++neighbors;
                }
            }
            if (GameMode == 2) {
                if (IsOccupied(row, col)) {
                    // Add its own reflection
                    ++neighbors;
                }
            }
            if (IsOccupied(row, col + 1)) {
                ++neighbors;
                if (GameMode == 2) {
                    // since we have a mirror image we can increment it again
                    ++neighbors;
                }
            }
            if (IsOccupied(row - 1, col + 1)) {
                ++neighbors;
            }
            if (IsOccupied(row, col - 1)) {
                ++neighbors;
                if (GameMode == 2) {
                    // since we have a mirror image we can increment it again
                    ++neighbors;
                }
            }
            if (IsOccupied(row - 1, col)) {
                ++neighbors;
            }
            if (IsOccupied(row - 1, col - 1)) {
                ++neighbors;
            }
        }
    }
    // in between rows
    if ((row != 0) && (row != (my_height -1))) {
        if (col == 0) {
            if (GameMode == 1) {
                // doughnut mode with wrap around
                if (IsOccupied(row - 1, my_width-1)) {
                    ++neighbors;
                }
                if (IsOccupied(row, my_width - 1)) {
                    ++neighbors;
                }
                if (IsOccupied(row + 1, my_width - 1)) {
                    ++neighbors;
                }
            }
            if (GameMode == 2) {
                if (IsOccupied(row, col)) {
                    // Add its own reflection
                    ++neighbors;
                }
            }
            if (IsOccupied(row, col + 1)) {
                ++neighbors;
            }
            if (IsOccupied(row + 1, col)) {
                ++neighbors;
                if (GameMode == 2) {
                     ++neighbors;
                }
            }
            if (IsOccupied(row + 1, col + 1)) {
                ++neighbors;
            }
            if (IsOccupied(row - 1, col)) {
                if (GameMode == 2) {
                     ++neighbors;
                }
                ++neighbors;
            }
            if (IsOccupied(row - 1, col + 1)) {
                ++neighbors;
            }
        }
        else if (col == (my_width - 1)) { 
            if (GameMode == 1) {
                // doughnut mode with wrap around
                if (IsOccupied(row - 1, 0)) {
                    ++neighbors;
                }
                if (IsOccupied(row, 0)) {
                    ++neighbors;
                }
                if (IsOccupied(row + 1, 0)) {
                    ++neighbors;
                }
            }
            if (GameMode == 2) {
                if (IsOccupied(row, col)) {
                    // Add its own reflection
                    ++neighbors;
                }
            }
            if (IsOccupied(row, col - 1)) {
                ++neighbors;             
            }
            if (IsOccupied(row + 1, col)) {
                ++neighbors;
                if (GameMode == 2) {
                    ++neighbors;
                }
            }
            if (IsOccupied(row + 1, col - 1)) {
                ++neighbors;
            }
            if (IsOccupied(row - 1, col)) {
                ++neighbors;
                if (GameMode == 2) {
                    ++neighbors;
                }
            }
            if (IsOccupied(row - 1, col - 1)) {
                ++neighbors;
            }
        }
        else {
            if (IsOccupied(row, col + 1)) {
                ++neighbors;
            }
            if (IsOccupied(row + 1, col + 1)) {
                ++neighbors;
            }
            if (IsOccupied(row, col - 1)) {
                ++neighbors;
            }
            if (IsOccupied(row + 1, col)) {
                ++neighbors;
            }
            if (IsOccupied(row + 1, col - 1)) {
                ++neighbors;
            }
            if (IsOccupied(row - 1, col)) {
                ++neighbors;
            }
            if (IsOccupied(row - 1, col - 1)) {
                ++neighbors;
            }
            if (IsOccupied(row - 1, col + 1)) {
                ++neighbors;
            }
        }
    }

    switch (neighbors) {
    case 0:
    case 1:
        return 0; // indicates empty next round
        break;
    case 2:
        return 1; // indicates stay as is
        break;
    case 3:
        return 2; // indicates occupied next round
        break;
    default:
        return 3; // indicates empty
        break;
    }
}

bool Grid::IsGridSame(Grid* newGrid) {
    // https://stackoverflow.com/questions/43432524/how-to-compare-two-2d-arrays-of-char-in-c-c
    // Returns true if the two grids contain the same values
    for (int i = 0; i < my_height; ++i) {
        for (int j = 0; j < my_width; ++j) {
            if (GridPtr[i][j].getIsOccupied() != newGrid->IsOccupied(i,j)){
                return false;
            }
        }
    }

    return true;

}

void Grid::initGrid(float density) {
    // Initializes the grid by populating the cells to either alive or dead 
    // based on the random number being less than density supplied
    // this should get us as close to the density requested
    for (int i = 0; i < my_width; ++i) {
        for (int j = 0; j < my_height; j++) {
            if (getRandomNumber() < density) {
                //cout << "Its alive " << endl;
                location cell(true);
                (GridPtr[i])[j] = cell;
            }
            else {
                //cout << "It's dead " << endl;
                location cell(false);
                (GridPtr[i])[j] = cell;
            }
        }
    }
}

float Grid::getRandomNumber() {
    // https://stackoverflow.com/questions/48716109/generating-a-random-number-between-0-1-c
    // Random number generator between 0 to 1
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1
    float randomNumber = dis(gen);
    return randomNumber;
}
