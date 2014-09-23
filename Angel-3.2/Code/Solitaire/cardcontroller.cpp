#include "cardcontroller.h"

void CardController::setLogicalPosition(int row, int position)
{
    _row = row;
    _position = position;
}

void CardController::setCard(Card card)
{
    _cardType = card.type;
    _cardValue = card.value;
}
