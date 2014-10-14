#include "game.h"
#include "window.h"

Game::Game()
    : _board(nullptr)
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
    theWindow.setHorizontalMargin(1.0);
    std::pair<int, int> resolution(1024, 768);
    theWorld.Initialize(resolution.first, resolution.second,
                        "Solitaire", false, false, false);
    theWindow.setResolution(resolution);
    theWorld.SetBackgroundColor(Color(0.0f, 0.60f, 0.16f));

    MoveInfo moveInfo;
    _board = new Board();
    _slogic.setNewBoard(moveInfo);
    _board->parseMoveInfo(moveInfo);

    // this function won't return until StopGame
    theWorld.StartGame();
}

/*static*/ void Game::stop()
{
    sysLog.Log("Stopping the game");
    // do all your setup first, because this function won't return until you're exiting
    theWorld.StopGame();
}

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}
