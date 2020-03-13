#include "game.h"

using namespace std;

int main(int argc, char** argv){
    Game sim;

    sim.start();
    sim.~Game();

    cout << "Press enter to exit" << endl;
    cin.get();
}
