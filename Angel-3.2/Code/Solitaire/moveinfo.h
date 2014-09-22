#ifndef MOVEINFO_H
#define MOVEINFO_H

#include <vector>
#include "card.h"

struct CardPosition
{
    CardPosition(int row_, int position_)
        : row(row_)
        , position(position_) {}
    int row, position;
};

struct Creation
{
    Creation(int row_, int position_, Card card_)
        : cardPosition(row_, position_)
        , card(card_) {}
    CardPosition cardPosition;
    Card card;
};

struct Swap
{
    Swap(int fromRow, int fromPosition,
         int toRow, int toPosition)
        : from(fromRow, fromPosition)
        , to(toRow, toPosition) {}
    CardPosition from, to;
};

struct MoveInfo
{
    void addCreation(Creation c);
    void addSwap(Swap s);

    const std::vector<Swap> getSwaps() const;
    const std::vector<Creation> getCreations() const;

private:
    std::vector<Creation> _creations;
    std::vector<Swap> _swaps;
};

#endif // MOVEINFO_H
