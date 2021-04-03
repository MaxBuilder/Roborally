#ifndef PROJET_ARTIFICIALPLAYER_HPP
#define PROJET_ARTIFICIALPLAYER_HPP

#include "boardGraph.hpp"
#include "moveDeck.hpp"

#include <iostream>


class artificialPlayer {
public:
    explicit artificialPlayer(boardGraph& graph);
    std::vector<Play> play(Robot origin, Location destination, moveDeck& deck);

private:
    // Elements de A* :
    struct Node {
        Robot current;
        Robot parent;
        int heuristic{};
        int costSoFar{};
        std::vector<Robot::Move> hand;
        int movesLeft{};
        Robot::Move transition;

        Node() = default;
        Node(Robot current, Robot parent, int heursitic, int costSoFar, const std::vector<Robot::Move>& hand, int movesLeft, Robot::Move transition);

        /*
        Node& operator = (const Node& n) {
            current.location.line = n.current.location.line;
            current.location.column = n.current.location.column;
            current.status = n.current.status;

            parent.location.line = n.parent.location.line;
            parent.location.column = n.parent.location.column;
            parent.status = n.parent.status;

            heuristic = n.heuristic;
            costSoFar = n.costSoFar;
            movesLeft = n.movesLeft;
            transition = n.transition;

            hand.clear();
            for(auto m : n.hand)
                hand.push_back(m);

            return *this;
        }*/
    };

    boardGraph mGraph;

    struct NodeComp {
        bool operator () (const Node& lhs, const Node& rhs) { return lhs.heuristic > rhs.heuristic; }
    };

    bool checkTransition(Node& n);
    int distance(Location l1, Location l2);
    bool isInClosedList(std::queue<Node> closedList, const Node &node);
    bool isInOpenListWithLowerCost(std::priority_queue<Node, std::vector<Node>, NodeComp> openList, const Node &n);
    std::vector<Play> buildPath(Node& destination, std::queue<Node> closedList, Robot origin);
};

#endif //PROJET_ARTIFICIALPLAYER_HPP
