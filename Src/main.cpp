#include "board.hpp"
#include "boardGraph.hpp"

#include <iostream>

int main() {
    RR::Board b("Data/board.txt") ;
    boardGraph graph(b);
    std::cout << std::endl << "-----------------------------------------------------------------" << std::endl << std::endl;

    Robot start = Robot({0, 1}, Robot::Status::EAST);
    Robot end = Robot({3, 4}, Robot::Status::EAST);
    Location endLoc = Location(3, 4);
    auto path = graph.path(start, end);

    std::cout << "Plus court chemin entre : " << start << " et " << end << std::endl;
    for(auto& step : path) {
        std::cout << step.robot << " -> " << step.move << std::endl;
    }
    std::cout << end << " - Terminé" << std::endl;

    std::cout << std::endl << "Vérification :" << std::endl;
    Robot test = start;
    for(auto& step : path) {
        std::cout << step.robot << std::endl;
        b.play(test, step.move);
    }
    std::cout << test << std::endl;

    std::cout << std::endl << "-----------------------------------------------------------------" << std::endl << std::endl;

    // Joueur artificiel

    return 0 ;
}