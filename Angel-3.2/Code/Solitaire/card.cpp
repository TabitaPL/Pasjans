#include "card.h"

/*static*/ std::string Card::toString(Type t)
{
    switch (t)
    {
        case Type::CLUB :
            return "CLUB";
        case Type::HEART :
            return "HEART";
        case Type::SPADE :
            return "SPADE";
        case Type::DIAMOND :
            return "DIAMOND";
        case Type::COUNT :
            return "COUNT";
        default:
            return "";
    }
}

/*static*/ std::string Card::toString(Value v)
{
    switch (v)
    {
        case Value::TWO :
            return "TWO";
        case Value::THREE :
            return "THREE";
        case Value::FOUR :
            return "FOUR";
        case Value::FIVE :
            return "FIVE";
        case Value::SIX :
            return "SIX";
        case Value::SEVEN :
            return "SEVEN";
        case Value::EIGHT :
            return "EIGHT";
        case Value::NINE :
            return "NINE";
        case Value::TEN :
            return "TEN";
        case Value::JACK :
            return "JACK";
        case Value::QUEEN :
            return "QUEEN";
        case Value::KING :
            return "KING";
        case Value::ACE :
            return "ACE";
        case Value::COUNT :
            return "COUNT";
        default:
            return "";
    }
}

std::string Card::toString() const
{
    return Card::toString(type) + " " + Card::toString(value);
}
