#include "game.h"
#include "window.h"
#include "backlightactor.h"

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
    std::pair<int, int> resolution(640, 480);
    theWorld.Initialize(resolution.first, resolution.second,
                        "Solitaire", false, false, false);
    theWindow.setResolution(resolution);
//    theWorld.SetBackgroundColor(Color(0.0f, 0.60f, 0.16f));

//    MoveInfo moveInfo;
//    _board = new Board();
//    _slogic.setNewBoard(moveInfo);
//    _board->parseMoveInfo(moveInfo);
    BacklightActor backlightActor;
    theWorld.Add(&backlightActor);

    auto t = new TextActor("Console", "Here's a ParticleActor. (Try moving and clicking the mouse!)");
    t->SetPosition(0, 3.5);
    t->SetAlignment(TXT_Center);
    theWorld.Add(t);
    auto t2 = new TextActor("Console", "Press [B] to change its properties.");
    t2->SetPosition(0, 2.5);
    t2->SetAlignment(TXT_Center);
    theWorld.Add(t2);
    TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenParticleActors.cpp");
    fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
    fileLoc->SetColor(.3f, .3f, .3f);
    theWorld.Add(fileLoc);

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
