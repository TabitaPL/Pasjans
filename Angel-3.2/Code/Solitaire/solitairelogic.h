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

    /*
     * SOLUTIONS:
     *
     * 1) add EMPTY to card type&value
     *    this complicates things, and breaks convention, since we won't be able to use COUNT like before
     * 2) add isEmpty to Card - which is stupid, because Card is a card
     * 3) Create CardPlace, which contains pointer to Card - may be null
     * 4) Store pointers to Cards in m_cards - null means empty space;
     *
     */
};

#endif // SOLITAIRELOGIC_H
