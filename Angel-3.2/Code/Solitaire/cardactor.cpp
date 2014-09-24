#include "cardactor.h"
#include "window.h"

void CardActor::setLogicalPosition(int row, int column)
{
    _row = row;
    _column = column;
}

void CardActor::setCard(Card card)
{
    _cardType = card.type;
    _cardValue = card.value;
}

float CardActor::getWidth() const
{
    return _width;
}

float CardActor::getHeight() const
{
    return _height;
}

void CardActor::setWidth(float w)
{
    _width = w;
    _height = _width / 0.65f;
}


