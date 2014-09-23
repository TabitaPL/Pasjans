#include "cardcontroller.h"

void CardController::setLogicalPosition(int row, int column)
{
    _row = row;
    _column = column;
}

void CardController::setCard(Card card)
{
    _cardType = card.type;
    _cardValue = card.value;
}
