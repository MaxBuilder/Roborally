#include "MoveDeck.hpp"

#include <random>

MoveDeck::MoveDeck() : moveDrawn(0) {}

void MoveDeck::shuffle() {
    std::shuffle(moves.begin(), moves.end(), std::mt19937(std::random_device()()));
}

void MoveDeck::add(Robot::Move move, int nb) {
    for(int i = 0 ; i < nb ; i++)
        moves.push_back(move);
}

std::vector<Robot::Move> MoveDeck::draw(int nb) {
    std::vector<Robot::Move> res;
    res.reserve(nb);
    for(int i = 0 ; i < nb ; i++) {
        res.push_back(moves[moveDrawn++]);
        if(moveDrawn == moves.size())
            shuffle();
    }
    return res;
}