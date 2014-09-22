#include "game.h"

Game::Game()
{
}

Game::~Game()
{
    sysLog.Log("End of the game");
    if (_board != nullptr)
        delete _board;
    _board = nullptr;
    // any cleanup can go here
    theWorld.Destroy();
}

/*static*/ void Game::start()
{
    sysLog.Log("Start of the game");
    _board = new Board();
    _slogic.setNewBoard(moveInfo);
    std::vector<Card> * cards = _slogic.getCards();
    _board->setCards(cards);

    // this function won't return until StopGame
    theWorld.StartGame();
}

/*static*/ void Game::stop()
{
    sysLog.Log("End of the game");
    // do all your setup first, because this function won't return until you're exiting
    theWorld.StopGame();
}

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}
