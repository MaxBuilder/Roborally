#ifndef PROJET_ARTIFICIALPLAYER_HPP
#define PROJET_ARTIFICIALPLAYER_HPP

#include "BoardGraph.hpp"
#include "MoveDeck.hpp"

class ArtificialPlayer {
public:
    // Initialise le joueur artificiel avec un graph
    explicit ArtificialPlayer(BoardGraph& graph);

    // Chemin le plus court en fonction d'un set de mouvements (implémentation de a*)
    std::vector<Robot::Move> play(Robot origin, Location destination, std::vector<Robot::Move>& deck);

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

        //Node() = default;
        Node(Robot current, Robot parent, int heursitic, int costSoFar, const std::vector<Robot::Move>& hand, int movesLeft, Robot::Move transition);
    };

    // Graphe du plateau
    BoardGraph mGraph;

    // Foncteur de comparaison entre sommets de a*
    struct NodeComp {
        bool operator () (const Node& lhs, const Node& rhs) { return lhs.heuristic > rhs.heuristic; }
    };

    // Fonction auxiliaires
    static bool checkTransition(Node& n);
    static int approx(Location l1, Location l2);
    static bool isInClosedList(std::queue<Node> closedList, const Node &node);
    static bool isInOpenListWithLowerCost(std::priority_queue<Node, std::vector<Node>, NodeComp> openList, const Node &n);

    // Reconstruit le chemin à parcourir après traitement des sommets par a*
    static std::vector<Robot::Move> buildPath(Robot origin, Node& destination, const std::queue<Node>& closedList);
};

#endif //PROJET_ARTIFICIALPLAYER_HPP
