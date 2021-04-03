#ifndef PROJET_ARTIFICIALPLAYER_HPP
#define PROJET_ARTIFICIALPLAYER_HPP

#include "boardGraph.hpp"
#include "moveDeck.hpp"

class artificialPlayer {
public:
    explicit artificialPlayer(boardGraph& graph);
    std::vector<Play> play(Robot origin, Location destination, moveDeck& deck);

private:
    // Elements de A* :
    struct Node {
        Robot current;
        Robot parent;
        int heuristic;
        int costSoFar;
        std::vector<Robot::Move> hand;
        int movesLeft;
        Robot::Move transition;

        Node(Robot current, Robot parent, int heursitic, int costSoFar, const std::vector<Robot::Move>& hand, int movesLeft, Robot::Move transition);
    };

    boardGraph mGraph;

    struct NodeComp {
        bool operator () (const Node& lhs, const Node& rhs) { return lhs.heuristic > rhs.heuristic; }
    };

    bool checkTransition(Node& n);
    int distance(Location l1, Location l2);
    bool isInClosedList(std::queue<Node> closedList, artificialPlayer::Node &node);
    bool isInOpenListWithLowerCost(std::priority_queue<Node, std::vector<Node>, NodeComp> openList, artificialPlayer::Node &n);
    std::vector<Play> buildPath(Node& destination, std::queue<Node> closedList);
};

#endif //PROJET_ARTIFICIALPLAYER_HPP
