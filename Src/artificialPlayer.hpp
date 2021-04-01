#ifndef PROJET_ARTIFICIALPLAYER_HPP
#define PROJET_ARTIFICIALPLAYER_HPP

#include "boardGraph.hpp"
#include "moveDeck.hpp"

class artificialPlayer {
public:
    explicit artificialPlayer(boardGraph& graph);
    std::vector<Play> play(Robot origin, Location destination, const moveDeck& deck);

private:
    boardGraph mGraph;

    // A* elements :
    struct Node {
        Location location;
        int heuristic;
        std::vector<Robot::Move> hand;
        int movesLeft;
        // ...
    };

    struct NodeComp {
        bool operator () (const Node& lhs, const Node& rhs) {return lhs.heuristic > rhs.heuristic; }
    };
};

#endif //PROJET_ARTIFICIALPLAYER_HPP
