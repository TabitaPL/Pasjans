#include "card.h"

Vector2 Card::getSize() const
{
    return _size;
}

Card::Type Card::getType() const
{
    return _type;
}

Card::Value Card::getValue() const
{
    return _value;
}

void Card::setSize(Vector2 &size)
{
    _size = size;
}

void Card::setSize(float x, float y)
{
    _size.X = x;
    _size.X = y;
}

void Card::setType(Card::Type &type)
{
    _type = type;
}

void Card::setValue(Card::Value &value)
{
    _value = value;
}
