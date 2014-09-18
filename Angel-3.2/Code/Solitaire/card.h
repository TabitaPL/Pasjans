#ifndef CARD_H
#define CARD_H

#include <Angel.h>

class Card
{
public:
    enum class Type {
    CLUB,
    HEART,
    SPADE,
    DIAMOND
  };

    enum class Value {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
  };
    Vector2 getSize() const;
    Type getType() const;
    Value getValue() const;
    void setSize(Vector2& size);
    void setSize(float x, float y);
    void setType(Type& type);
    void setValue(Value& value);

private:
    Vector2 _size;
    Type _type;
    Value _value;
};

#endif // CARD_H
