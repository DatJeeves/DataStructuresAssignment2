#include "game.h"
#include <cstdlib>
#include <fstream>
#include <random>
#include <thread>
#include <chrono>


using namespace std;
//constructor class
Game::Game(){
    
}

Game::~Game(){
    //https://stackoverflow.com/questions/584868/rerouting-stdin-and-stdout-from-c
    // Need to redirect to stdout just in case
    freopen("/dev/tty", "w", stdout);

}


void Game::start() {
    Input user;

    // Get the user input
    user.GetConfiguration();

    // Set up 2 grids that are identical for initial starting point
    if (user.IsPreconfigWorld) {
        g1 = new Grid(user.PreconfigFileName);
        g2 = new Grid(user.PreconfigFileName);
    }
    else {
        g1 = new Grid(user.GridHeight, user.GridWidth, user.Density);
        g2 = new Grid(user.GridHeight, user.GridWidth, user.Density);
    }

    // Make one current and the other the future
    currentGrid = g1;
    futureGrid = g2;


    // Intial generation 0 is the starting point
    cout << "0" << endl;
    currentGrid->displayGrid();

    int r = 1;
    do {

        round(r, user.GameMode);

        
        // After each round switch the grids so we always make the future current
        if (r % 2) {
            currentGrid = g1;
            futureGrid = g2;
        }
        else {
            currentGrid = g2;
            futureGrid = g1;
        }


        // 0 = Pause between generations using system ("pause")
        if (user.OutputMode == 0) {
            // http://www.cplusplus.com/reference/thread/this_thread/sleep_for/
            // Changing system("pause") to sleep_for
            //system("pause");

            this_thread::sleep_for(chrono::seconds(1));
        }
        else if (user.OutputMode == 1) {
         // 1 = Hit enter between generations
            // http://www.cplusplus.com/forum/beginner/7379/
            cout << "Hit enter to continue ..." << endl;
            cin.get();
        }
        else
        {
            // 2 = output to a file
        }

        ++r;
    } while (!currentGrid->IsGridSame(futureGrid));

    
}

void Game::round(int generation, int GameMode) {
    // Start with the assumption that the grid changed at the begining
    // of the round.
    for (int i = 0; i < currentGrid->my_height; ++i) {
        for (int j = 0; j < currentGrid->my_width; j++) {
            switch (currentGrid->CheckNextState(i, j, GameMode)) {
                case 1:
                    //Indicates stay as is
                    if (currentGrid->IsOccupied(i, j)) {
                        futureGrid->SetOccupied(i, j);
                    }
                    else {
                        futureGrid->ClearOccupied(i, j);
                    }
                    
                    break;
                case 2:
                    // Indicates will be occupied next round
                    futureGrid->SetOccupied(i, j);
                    break;
                default:
                    // Indicates nextround is empty cell
                    futureGrid->ClearOccupied(i, j);
                    break;
            }
        }
    }

    cout << "generation " << generation << endl;
    futureGrid->displayGrid();
}
