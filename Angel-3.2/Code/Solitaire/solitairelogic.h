#ifndef SOLITAIRELOGIC_H
#define SOLITAIRELOGIC_H

#include <vector>

#include "card.h"

class SolitaireLogic
{
public:
    SolitaireLogic();

private:
    std::vector<Card> m_cards[4];
};

#endif // SOLITAIRELOGIC_H
