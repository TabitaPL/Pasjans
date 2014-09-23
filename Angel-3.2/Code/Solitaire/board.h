#ifndef BOARD_H
#define BOARD_H

#include <Angel.h>

class Card;
/*
 * This class is responsible for:
 * 1) drawing background
 * 2) cards management
 * 3) Mouse handling
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
    void registerCardFilenames();
    String _nameOfClickedCard;
    std::vector<Renderable*> _objects; //all of objects on board
    std::map<Card, std::string> _cardsRegistry;
};

#endif // BOARD_H
