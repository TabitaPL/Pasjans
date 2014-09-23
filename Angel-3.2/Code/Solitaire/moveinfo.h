#ifndef MOVEINFO_H
#define MOVEINFO_H

#include <vector>
#include "card.h"

struct CardPosition
{
    CardPosition(int row_, int offset_)
        : row(row_)
        , column(offset_) {}
    int row, column;
};

struct Creation
{
    Creation(int row_, int column_, Card card_)
        : position(row_, column_)
        , card(card_) {}
    CardPosition position;
    Card card;
};

struct Swap
{
    Swap(int fromRow, int fromOffset,
         int toRow, int toOffset)
        : from(fromRow, fromOffset)
        , to(toRow, toOffset) {}
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
