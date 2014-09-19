#include <random>
#include <time.h>
#include "solitairelogic.h"

SolitaireLogic::SolitaireLogic()
{
    srand(time(NULL));
    m_deck.clear();
    for (int i = 0; i < int(Card::Type::COUNT); i++)
        for (int j = 0; j < int(Card::Value::COUNT); j++)
           m_deck.push_back(Card(Card::Type(i), Card::Value(j)));

    for (int i = 0; i < 4; i++)
        m_cards[i] = &
}

void SolitaireLogic::setNewBoard()
{
    // basically we need to shuffle our m_deck
    // and divide it in 4 to set m_cards
}
