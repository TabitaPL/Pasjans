#ifndef BOARD_H
#define BOARD_H

#include <Angel.h>

class Card;
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
    void setCards(std::vector<Card>* cards);

    virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);
private:
    String _nameOfClickedCard;
    std::vector<Renderable*> _objects; //all of objects on board

};

#endif // BOARD_H
