#include "BoardGraph.hpp"
#include "MoveDeck.hpp"
#include "ArtificialPlayer.hpp"

#include <iostream>

int main() {
    std::cout << "Chargement du plateau ... ";
    RR::Board b("Data/board.txt") ;
    BoardGraph graph(b);
    std::cout << "OK !" << std::endl;

    // Variables de test :
    Robot start = Robot({0, 1}, Robot::Status::EAST); // 5,4
    Location endLoc = Location(5, 4);
    Robot end = Robot(endLoc, Robot::Status::EAST);


    std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
    std::cout << "Plus court chemin entre deux cases : " << std::endl << std::endl;

    auto path1 = graph.path(start, end);

    std::cout << "Plus court chemin entre " << start << " et " << end << " : " << std::endl;
    for(auto& step : path1) {
        std::cout << step << std::endl;
    }

    std::cout << std::endl << "Verification avec le plateau :" << std::endl;
    Robot test1 = start;
    for(auto& step : path1) {
        std::cout << test1 << " -> " << step << std::endl;
        b.play(test1, step);
    }
    std::cout << test1 << std::endl;

    std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
    std::cout << "Plus court chemin entre deux cases (orientation finale quelconque) : " << std::endl << std::endl;

    auto path2 = graph.path(start, endLoc);

    std::cout << "Plus court chemin entre " << start << " et " << endLoc.line << "," << endLoc.column << " : " <<std::endl;
    for(auto& step : path2) {
        std::cout << step << std::endl;
    }

    std::cout << std::endl << "Verification avec le plateau :" << std::endl;
    Robot test2 = start;
    for(auto& step : path2) {
        std::cout << test2 << " -> " << step << std::endl;
        b.play(test2, step);
    }
    std::cout << test2 << std::endl;

    std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
    std::cout << "Utilisation d'un joueur artificiel et d'un deck avec tirage aleatoire : " << std::endl << std::endl;

    MoveDeck deck;
    deck.add(Robot::Move::FORWARD_1, 3);
    deck.add(Robot::Move::FORWARD_2, 2);
    deck.add(Robot::Move::FORWARD_3, 1);
    deck.add(Robot::Move::BACKWARD_1, 2);
    deck.add(Robot::Move::TURN_LEFT, 1);
    deck.add(Robot::Move::TURN_RIGHT, 1);
    deck.add(Robot::Move::U_TURN, 1);
    deck.shuffle();

    // Tirage des mouvements (peut être directement mis dans l'appel, fait ici pour afficher)
    auto drawn = deck.draw();
    std::cout << "Coups possibles : " << std::endl;
    for(auto move : drawn) {
        std::cout << move << std::endl;
    }
    std::cout << std::endl;

    ArtificialPlayer player(graph);
    auto autoPath = player.play(start, endLoc, drawn);

    std::cout << "Chemin avec le deck entre " << start << " et " << endLoc.line << "," << endLoc.column << " : " << std::endl;
    for(auto& step : autoPath) {
        std::cout << step << std::endl;
    }

    std::cout << std::endl << "Verification avec le plateau:" << std::endl;
    Robot test3 = start;
    for(auto& step : autoPath) {
        std::cout << test3 << " -> " << step << std::endl;
        b.play(test3, step);
    }
    std::cout << test3 << std::endl;

    std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
    return 0 ;
}