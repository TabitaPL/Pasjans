#ifndef MOVEINFO_H
#define MOVEINFO_H

#include <vector>
#include "card.h"

struct CardPosition
{
    CardPosition(int row_, int offset_)
        : row(row_)
        , offset(offset_) {}
    int row, offset;
};

struct Creation
{
    Creation(int row_, int offset_, Card card_)
        : position(row_, offset_)
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
