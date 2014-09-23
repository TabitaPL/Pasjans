#ifndef BOARD_H
#define BOARD_H

#include "AngelHeader.h"
#include "moveinfo.h"

class Card;
class CardController;
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
    void parseMoveInfo(const MoveInfo& moveInfo);

    virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);
private:
    void registerCardFilenames();

    String _nameOfClickedCard;
    std::vector<std::vector<CardController*>> _cards;
    std::map<Card, std::string> _cardsRegistry;
};

#endif // BOARD_H
