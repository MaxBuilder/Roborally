#include "artificialPlayer.hpp"

artificialPlayer::Node::Node(Robot c, Robot p, int h, int cost, const std::vector<Robot::Move>& m, int ml, Robot::Move t)
: current(c), parent(p), heuristic(h), costSoFar(cost), hand(m), movesLeft(ml), transition(t) {

}

artificialPlayer::artificialPlayer(boardGraph& graph)
: mGraph(graph) {}

std::vector<Play> artificialPlayer::play(Robot origin, Location destination, moveDeck& deck) {
    // Variables de l'algorithme a* :
    std::priority_queue<Node, std::vector<Node>, NodeComp> openList;
    std::queue<Node> closedList;

    // Tirage des mouvements (cout pour le debug)
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

        std::cout << u.current << " " << u.movesLeft << std::endl;
        if(u.current.location == destination) { // Si le but est atteint on reconstruit le chemin
            std::cout << "Found !!!";
            return buildPath(u, closedList, origin);
        }

        auto transitions = mGraph.getTransitions(u.current);
        //std::cout << "Nouveau sommet" << std::endl;
        for(auto transition : transitions) { // Exploration des voisins
            int cost = u.costSoFar + 1;
            int heuristic = cost + distance(destination, transition.robot.location);
            Node v(transition.robot, u.current, heuristic, cost, u.hand, u.movesLeft, transition.move);
            std::cout << "v : " << v.current << " " << v.movesLeft << std::endl;

            if(!checkTransition(v)) {
                //std::cout << "Cut transition" << std::endl;
                continue;
            }
            //std::cout << "Go transition" << std::endl;

            if(!isInClosedList(closedList, v)) {
                if(isInOpenListWithLowerCost(openList, v)) {

                    // Mise à jour du coût
                    std::queue<Node> temp;
                    while(!openList.empty()) {
                        Node tempNode = openList.top();
                        openList.pop();
                        if(tempNode.current == v.current)
                            tempNode = v;
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

    // Approximation du sommet le plus proche
    return std::vector<Play>();

}

std::vector<Play> artificialPlayer::buildPath(Node &destination, std::queue<Node> closedList, Robot origin) {
    std::vector<Play> res;
    Node temp = destination;
    while(temp.current != origin) {
        std::queue<Node> tempQ = closedList;
        res.emplace_back(temp.parent, temp.transition);
        while(tempQ.front().parent != temp.parent)
            tempQ.pop();

        temp = tempQ.front();
    }

    std::reverse(res.begin(), res.end());
    return res;
}

bool artificialPlayer::isInOpenListWithLowerCost(std::priority_queue<Node, std::vector<Node>, NodeComp> openList, const Node &n) {
    while(!openList.empty()) {
        Node l = openList.top();
        if(l.current == n.current and l.costSoFar > n.costSoFar)
            return true;
        openList.pop();
    }
    return false;
}

bool artificialPlayer::isInClosedList(std::queue<Node> closedList, const Node &node) {
    while(!closedList.empty()) {
        if(closedList.front().current == node.current)
            return true;
        closedList.pop();
    }
    return false;
}

bool artificialPlayer::checkTransition(Node &n) {
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

int artificialPlayer::distance(Location l1, Location l2) {
    int d = std::abs(l1.line - l2.line) + std::abs(l1.column - l2.column);
    int r = 0;
    if(d % 3 != 0)
        r = 1;
    int h = d / 3 + r;
    return h;
}
