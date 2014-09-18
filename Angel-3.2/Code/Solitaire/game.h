#ifndef GAME_H
#define GAME_H

#include <Angel.h>

#define theGame Game::getInstance()

class Game
{
public:
    void start();
    static Game& getInstance();
    ~Game();
private:
    Game();
};

#endif // GAME_H
