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
    std::pair<int, int> resolution(640, 480);
    theWorld.Initialize(resolution.first, resolution.second,
                        "Solitaire", false, false, false);
    theWindow.setResolution(resolution);
//    theWorld.SetBackgroundColor(Color(0.0f, 0.60f, 0.16f));

//    MoveInfo moveInfo;
//    _board = new Board();
//    _slogic.setNewBoard(moveInfo);
//    _board->parseMoveInfo(moveInfo);

    ParticleActor *pa = new ParticleActor();
    pa->SetColor(1.0f, 1.0f, 0.0f);  //Sets the initial color of the particles.
                                     // Since the image file we'll be using already
                                     // has a color, we set this to pure white.

    pa->SetSize(Vector2(0.2f, 0.2f)); //The size of each particle, in GL units
    //pa->SetSprite("Resources/Images/PNG-cards-1.3/CLUB/2.png"); //The image file we want to use (otherwise
                                                // it'll just be colored squares).
    pa->SetMaxParticles(500); //The maximum number of particles this system will ever handle.
    pa->SetParticlesPerSecond(100.0f); //Emission Rate
    pa->SetParticleLifetime(1.5f); //How long each particles lasts before disappearing
    pa->SetSpread(MathUtil::Pi / 360); //The angle in radians at which particles will be emitted.
    pa->SetEndScale(2.0f); //If you want the particles to change size over their lifetimes
    pa->SetEndColor(Color(1.0f, 1.0f, 1.0f, 0.0f)); //Our particles disappear over time
    pa->SetSpeedRange(3.0f, 4.0f); //The minimum and maximum range of speeds (so you can have
                                   // some variation).
    pa->SetGravity(Vector2::Zero); //You can pull the particles in a particular direction (default is
                                   // downwards, so zero it out if you need to).
    theWorld.Add(pa);

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
