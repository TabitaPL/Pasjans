#ifndef CARDCONTROLLER_H
#define CARDCONTROLLER_H

#include "AngelHeader.h"
#include "card.h"

class CardController : public Actor
{
public:
    void setLogicalPosition(int row, int position);
    void setCard(Card card);

private:
    Card::Type _cardType;
    Card::Value _cardValue;

    int _row, _position;
};

#endif // CARDCONTROLLER_H
