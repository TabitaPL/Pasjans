#ifndef CARDCONTROLLER_H
#define CARDCONTROLLER_H

#include "AngelHeader.h"
#include "card.h"

class CardActor : public Actor
{
public:
    void setLogicalPosition(int row, int column);
    void setCard(Card const * const card); // set type and value for card

    void setWidth(float w);

private:
    Card::Type _cardType;
    Card::Value _cardValue;

    int _row, _column;
};

#endif // CARDCONTROLLER_H
