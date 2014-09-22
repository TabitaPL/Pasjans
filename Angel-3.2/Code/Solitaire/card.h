#ifndef CARD_H
#define CARD_H

#include <iostream>

struct Card
{
    enum class Type {
        CLUB,
        HEART,
        SPADE,
        DIAMOND,
        COUNT
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
        ACE,
        COUNT
    };

    Card(Type t, Value v)
       : type(t), value(v)
    {}
    static std::string toString(Type t);
    static std::string toString(Value v);
    std::string toString();
    std::string getFileName();

    Type type;
    Value value;
};


#endif // CARD_H
