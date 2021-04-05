#include "ArtificialPlayer.hpp"

ArtificialPlayer::Node::Node(Robot c, Robot p, int h, int cost, const std::vector<Robot::Move>& m, int ml, Robot::Move t)
: current(c), parent(p), heuristic(h), costSoFar(cost), hand(m), movesLeft(ml), transition(t) {

}

ArtificialPlayer::ArtificialPlayer(BoardGraph& graph)
: mGraph(graph) {}

std::vector<Robot::Move> ArtificialPlayer::play(Robot origin, Location destination, std::vector<Robot::Move>& deck) {
    // Variables de l'algorithme a* :
    std::priority_queue<Node, std::vector<Node>, NodeComp> openList;
    std::queue<Node> closedList;

    // Ajout du sommet inital :
    openList.push(Node(origin, origin, 0, 0, deck, 5, Robot::Move::None));

    // Traitement des sommets :
    while(!openList.empty()) {
        Node u = openList.top();
        openList.pop();

        if(u.current.location == destination) // Si le but est atteint, on reconstruit le chemin
            return buildPath(origin, u, closedList);

        auto transitions = mGraph.getTransitions(u.current);
        for(auto transition : transitions) { // Exploration des voisins
            int cost = u.costSoFar + 1;
            int heuristic = cost + approx(destination, transition.robot.location);
            Node v(transition.robot, u.current, heuristic, cost, u.hand, u.movesLeft, transition.move);

            if(!checkTransition(v)) // Vérification de la possibilité de passer la transition
                continue;

            if(not isInClosedList(closedList, v) and not isInOpenListWithLowerCost(openList, v)) {
                 openList.push(v);
            }
        }
        closedList.push(u);
    }

    // Si aucun chemin n'est trouvé, on retourne un tableau vide
    return std::vector<Robot::Move>();

}

std::vector<Robot::Move> ArtificialPlayer::buildPath(Robot origin, Node& destination, const std::queue<Node>& closedList) {
    std::vector<Robot::Move> res;
    Node temp = destination;

    while(temp.current != origin) {
        std::queue<Node> tempQ = closedList;
        res.emplace_back(temp.transition);
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

int ArtificialPlayer::approx(Location l1, Location l2) {
    int d = std::abs(l1.line - l2.line) + std::abs(l1.column - l2.column);
    int r = 0;
    if(d % 3 != 0)
        r = 1;
    int h = d / 3 + r;
    return h;
}
