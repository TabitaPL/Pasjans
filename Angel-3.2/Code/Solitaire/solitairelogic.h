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

    Type m_type;
    Value m_value;
};

class SolitaireLogic
{
public:
    SolitaireLogic();
    void setNewBoard();

private:
    std::vector<Card> m_cards[4];   // representation of cards on the board
    std::vector<Card> m_deck;   // list of all possible cards
};

#endif // SOLITAIRELOGIC_H
