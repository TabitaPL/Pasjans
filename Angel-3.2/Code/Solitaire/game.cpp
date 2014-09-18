#include "game.h"

Game::Game()
{
}

Game::~Game()
{
    sysLog.Log("End of the game");
    // any cleanup can go here
    theWorld.Destroy();
}

/*static*/ void Game::start()
{
    sysLog.Log("Start of the game");
    // do all your setup first, because this function won't return until you're exiting
    theWorld.StartGame();
}

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}