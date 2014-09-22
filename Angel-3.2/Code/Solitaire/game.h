#ifndef GAME_H
#define GAME_H

#include <Angel.h>
#include "board.h"
#include "solitairelogic.h"

#define theGame Game::getInstance()

class Game : GameManager
{
public:
    void start();
    void stop();
    static Game& getInstance();
    ~Game();

private:
    Game();
    Board* _board;
    SolitaireLogic _slogic;
    MoveInfo moveInfo;
};

#endif // GAME_H
