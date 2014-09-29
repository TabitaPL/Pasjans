#include <random>
#include <time.h>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "solitairelogic.h"

SolitaireLogic::SolitaireLogic()
{
    srand(time(NULL));
    m_deck.clear();
    for (int i = 0; i < int(Card::Type::COUNT); i++)
        for (int j = 0; j < int(Card::Value::COUNT); j++)
           m_deck.push_back(Card(Card::Type(i), Card::Value(j)));
}

void SolitaireLogic::setNewBoard(MoveInfo &moveInfo)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_deck.begin(), m_deck.end(), g);

    int numberOfColumns = static_cast<int>(Card::Value::COUNT) + 1;  // +1 to account for the empty space
    for (int i = 0; i < static_cast<int>(Card::Type::COUNT); i++)
    {
        m_cards[i].clear();
        m_cards[i].push_back(nullptr);  // empty space
        moveInfo.addCreation(Creation(i, 0, nullptr));
        for (int j = 1; j < numberOfColumns; j++)
        {
            int offset = i * numberOfColumns + j;
            m_cards[i].push_back(&m_deck[offset]);
            moveInfo.addCreation(Creation(i, j, &m_deck[offset]));
        }
    }
}

std::vector<Card*> *SolitaireLogic::getCards()
{
    return m_cards;
}
