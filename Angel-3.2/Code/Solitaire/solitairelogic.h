#ifndef SOLITAIRELOGIC_H
#define SOLITAIRELOGIC_H

#include <vector>

struct Card
{
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

    Type type;
    Value value;
    };

class SolitaireLogic
{
public:
    SolitaireLogic();

private:
    std::vector<Card> m_cards[4];
};

#endif // SOLITAIRELOGIC_H
