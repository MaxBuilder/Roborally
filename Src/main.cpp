#include "boardGraph.hpp"
#include "moveDeck.hpp"
#include "artificialPlayer.hpp"

#include <iostream>

int main() {
    std::cout << "Chargement du plateau ... ";
    RR::Board b("Data/board.txt") ;
    boardGraph graph(b);
    std::cout << "OK !" << std::endl;

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

    std::cout << std::endl << "Vérification avec le plateau:" << std::endl;
    Robot test = start;
    for(auto& step : path) {
        std::cout << step.robot << std::endl;
        b.play(test, step.move);
    }
    std::cout << test << std::endl;

    std::cout << std::endl << "-----------------------------------------------------------------" << std::endl << std::endl;

    // Joueur artificiel
    moveDeck deck;
    deck.add(Robot::Move::FORWARD_1, 3);
    deck.add(Robot::Move::FORWARD_2, 2);
    deck.add(Robot::Move::FORWARD_3, 1);
    deck.add(Robot::Move::BACKWARD_1, 2);
    deck.add(Robot::Move::TURN_LEFT, 1);
    deck.add(Robot::Move::TURN_RIGHT, 1);
    deck.add(Robot::Move::U_TURN, 1);
    deck.shuffle();

    artificialPlayer player(graph);
    auto autoPath = player.play(start, endLoc, deck);

    std::cout << "Plus court chemin avec le deck entre : " << start << " et " << endLoc.line << "," << endLoc.column << std::endl;
    for(auto& step : path) {
        std::cout << step.robot << " -> " << step.move << std::endl;
    }
    std::cout << end << " - Terminé" << std::endl;

    return 0 ;
}