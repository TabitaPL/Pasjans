#include "moveinfo.h"

void MoveInfo::addCreation(Creation c)
{
    _creations.push_back(c);
}

void MoveInfo::addSwap(Swap s)
{
    _swaps.push_back(s);
}

const std::vector<Swap> MoveInfo::getSwaps() const
{
    return _swaps;
}

const std::vector<Creation> MoveInfo::getCreations() const
{
    return _creations;
}

