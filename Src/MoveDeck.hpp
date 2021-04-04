#ifndef PROJET_MOVEDECK_HPP
#define PROJET_MOVEDECK_HPP

#include "Board.hpp"

#include <algorithm>
#include <vector>

using namespace RR;

class MoveDeck {
public:
    MoveDeck();

    void shuffle();
    void add(Robot::Move move, int nb = 1);
    std::vector<Robot::Move> draw(int nb = 9);

private:
    std::vector<Robot::Move> moves;
    int moveDrawn;
};


#endif //PROJET_MOVEDECK_HPP
