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

    inline bool operator< (const Card& rhs) const
    {
        if (static_cast<int>(value) != static_cast<int>(rhs.value))
            return (static_cast<int>(value) < static_cast<int>(rhs.value));
        else
            return (static_cast<int>(type) < static_cast<int>(rhs.type));
    }

};


#endif // CARD_H
