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

void Game::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
    Vector2 clickedPlace = MathUtil::ScreenToWorld(screenCoordinates.X, screenCoordinates.Y);
    ActorSet cards = theTagList.GetObjectsTagged("card");
    String name = "";
    for (Actor* a : cards )
    {
        BoundingBox bbox = a->GetBoundingBox();
        if ( bbox.Intersects(clickedPlace, 0) )
        {
            name = a->GetName();
            a->SetSprite("Resources/Images/angel.png");
            break;
        }
    }
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
