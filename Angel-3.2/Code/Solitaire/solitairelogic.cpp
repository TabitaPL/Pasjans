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

    for (int i = 0; i < int(Card::Type::COUNT); i++)
        for (int j = 0; j < int(Card::Value::COUNT); j++)
        {
            int offset = i * int(Card::Value::COUNT) + j;
            m_cards[i].push_back(m_deck[offset]);
            moveInfo.addCreation(Creation(i, j, m_deck[offset]));
        }
}

std::vector<Card> *SolitaireLogic::getCards()
{
    return m_cards;
}
