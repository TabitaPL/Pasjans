#include "cardactor.h"
#include "window.h"

void CardActor::setLogicalPosition(int row, int column)
{
    _row = row;
    _column = column;
}

void CardActor::setCard(Card const * const card)
{
    _cardType = card->type;
    _cardValue = card->value;
}

void CardActor::setWidth(float w)
{
   SetSize(Vector2(w, w / 0.65f));
}


