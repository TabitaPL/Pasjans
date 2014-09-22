#ifndef SOLITAIRELOGIC_H
#define SOLITAIRELOGIC_H

#include <vector>

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
       : m_type(t), m_value(v)
    {}

    static std::string toString(Type t)
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

    static std::string toString(Value v)
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

    std::string toString()
    {
        return toString(m_type) + " " + toString(m_value);
    }

    std::string getFileName()
    {
        switch (m_value)
        {
            case Value::TWO :
                return "2.png";
            case Value::THREE :
                return "3.png";
            case Value::FOUR :
                return "4.png";
            case Value::FIVE :
                return "5.png";
            case Value::SIX :
                return "6.png";
            case Value::SEVEN :
                return "7.png";
            case Value::EIGHT :
                return "8.png";
            case Value::NINE :
                return "9.png";
            case Value::TEN :
                return "10.png";
            case Value::JACK :
                return "J.png";
            case Value::QUEEN :
                return "Q.png";
            case Value::KING :
                return "K.png";
            case Value::ACE :
                return "A.png";
            case Value::COUNT :
                return "";
            default:
                return "";
        }
    }

    Type m_type;
    Value m_value;

};

class SolitaireLogic
{
public:
    SolitaireLogic();
    void setNewBoard();
    std::vector<Card>* getCards();

private:
    std::vector<Card> m_cards[4];   // representation of cards on the board
    std::vector<Card> m_deck;   // list of all possible cards
};

#endif // SOLITAIRELOGIC_H
