#ifndef GAME_H
#define GAME_H

#include <Angel.h>

#define theGame Game::getInstance()

class Game : public MouseListener
{
public:
    void start();
    static Game& getInstance();
    ~Game();

    virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);
    //virtual void MouseMotionEvent(Vec2i screenCoordinates);

private:
    Game();
};

#endif // GAME_H
