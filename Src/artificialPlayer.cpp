#include "artificialPlayer.hpp"

artificialPlayer::artificialPlayer(boardGraph& graph)
: mGraph(graph) {}

std::vector<Play> artificialPlayer::play(Robot origin, Location destination, const moveDeck& deck) {
    // Variables de l'algorithme a* :
    std::priority_queue<Node, std::vector<Node>, NodeComp> openList;
    std::queue<Node> closedList;

    // Ajout du sommet inital :




}

