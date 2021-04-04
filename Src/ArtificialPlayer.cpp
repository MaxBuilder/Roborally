#include "ArtificialPlayer.hpp"

ArtificialPlayer::Node::Node(Robot c, Robot p, int h, int cost, const std::vector<Robot::Move>& m, int ml, Robot::Move t)
: current(c), parent(p), heuristic(h), costSoFar(cost), hand(m), movesLeft(ml), transition(t) {

}

ArtificialPlayer::ArtificialPlayer(BoardGraph& graph)
: mGraph(graph) {}

std::vector<Play> ArtificialPlayer::play(Robot origin, Location destination, MoveDeck& deck) {
    // Variables de l'algorithme a* :
    std::priority_queue<Node, std::vector<Node>, NodeComp> openList;
    std::queue<Node> closedList;

    // Tirage des mouvements (affichage pour le debug)
    auto d = deck.draw();
    std::cout << "Coups possibles : " << std::endl;
    for(auto m : d) {
        std::cout << m << std::endl;
    }
    std::cout << std::endl;

    // Ajout du sommet inital :
    openList.push(Node(origin, origin, 0, 0, d, 5, Robot::Move::None));

    // Traitement des sommets :
    while(!openList.empty()) {
        Node u = openList.top();
        openList.pop();

        if(u.current.location == destination) // Si le but est atteint on reconstruit le chemin
            return buildPath(origin, u, closedList);

        auto transitions = mGraph.getTransitions(u.current);
        for(auto transition : transitions) { // Exploration des voisins
            int cost = u.costSoFar + 1;
            int heuristic = cost + distance(destination, transition.robot.location);
            Node v(transition.robot, u.current, heuristic, cost, u.hand, u.movesLeft, transition.move);

            if(!checkTransition(v))
                continue;

            if(!isInClosedList(closedList, v)) {
                if(isInOpenListWithLowerCost(openList, v)) {

                    std::queue<Node> temp; // Mise à jour du coût (complexité catastrophique mais pas trop le choix)
                    while(!openList.empty()) {
                        Node tempNode = openList.top();
                        openList.pop();
                        if(tempNode.current == v.current) {
                            tempNode = v;
                        }
                        temp.push(tempNode);
                    }
                    while (!temp.empty()) {
                        openList.push(temp.front());
                        temp.pop();
                    }
                }
                else openList.push(v);
            }
        }
        closedList.push(u);
    }

    // Approximation du sommet le plus proche (à faire)
    return std::vector<Play>();

}

std::vector<Play> ArtificialPlayer::buildPath(Robot origin, Node& destination, std::queue<Node> closedList) {
    std::vector<Play> res;
    Node temp = destination;

    while(temp.current != origin) {
        std::queue<Node> tempQ = closedList;
        res.emplace_back(temp.parent, temp.transition);
        while(tempQ.front().current != temp.parent)
            tempQ.pop();
        temp = tempQ.front();
    }

    std::reverse(res.begin(), res.end());
    return res;
}

bool ArtificialPlayer::isInOpenListWithLowerCost(std::priority_queue<Node, std::vector<Node>, NodeComp> openList, const Node &n) {
    while(!openList.empty()) {
        Node l = openList.top();
        if(l.current == n.current and l.costSoFar > n.costSoFar)
            return true;
        openList.pop();
    }
    return false;
}

bool ArtificialPlayer::isInClosedList(std::queue<Node> closedList, const Node &node) {
    while(!closedList.empty()) {
        if(closedList.front().current == node.current)
            return true;
        closedList.pop();
    }
    return false;
}

bool ArtificialPlayer::checkTransition(Node &n) {
    if(n.movesLeft == 0)
        return false;

    for(auto it = n.hand.begin() ; it != n.hand.end() ; it++) {
        if(*it == n.transition) {
            n.hand.erase(it);
            n.movesLeft--;
            return true;
        }
    }

    return false;
}

int ArtificialPlayer::distance(Location l1, Location l2) {
    int d = std::abs(l1.line - l2.line) + std::abs(l1.column - l2.column);
    int r = 0;
    if(d % 3 != 0)
        r = 1;
    int h = d / 3 + r;
    return h;
}
