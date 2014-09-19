#include <iostream>
#include "game.h"
#include "board.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    Board *board = new Board();
    theGame.start();
    board = NULL;
    delete board;
    return 0;
}

