#ifndef BOARD_H
#define BOARD_H

#include <Angel.h>

/*
 * This class is responsible for:
 * 1) drawing background
 * 2) cards management
 *
 */
class Board : public MouseListener
{
public:
    Board();
    ~Board();
    void drawCards();

    virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);
private:
    String nameOfClickedCard;
};

#endif // BOARD_H
