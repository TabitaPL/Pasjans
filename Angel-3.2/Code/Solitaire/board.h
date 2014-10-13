#ifndef BOARD_H
#define BOARD_H

#include "AngelHeader.h"
#include "moveinfo.h"

class Card;
class CardActor;
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
    void parseMoveInfo(const MoveInfo& moveInfo);

    virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);
private:
    void registerCardFilenames();
	void drawFrame();
    void createCard(Creation creation);

    String _nameOfClickedCard;
    std::vector<std::vector<CardActor*>> _cards;
    std::vector<std::vector<Actor*>> _frames;
    std::map<Card, std::string> _cardsRegistry;
    float _spaceBetweenCards;
	float _cardWidth;
	const int _columnCount;
	const int _rowCount;
};

#endif // BOARD_H
