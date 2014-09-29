#ifndef SOLITAIRELOGIC_H
#define SOLITAIRELOGIC_H

#include <vector>
#include "moveinfo.h"

class SolitaireLogic
{
public:
    SolitaireLogic();
    void setNewBoard(MoveInfo &moveInfo);

private:
    std::vector<Card*> m_cards[4];   // representation of cards on the board
    std::vector<Card> m_deck;   // list of all possible cards
};

#endif // SOLITAIRELOGIC_H
