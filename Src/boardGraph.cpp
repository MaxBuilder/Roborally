//
// Created by raph on 3/27/21.
//

#include "boardGraph.hpp"

boardGraph::boardGraph(Board &board) { // Choix d'un parcours exhaustif de toutes les cases
    const std::vector<Robot::Move> moves = {
        Robot::Move::FORWARD_1,
        Robot::Move::FORWARD_2,
        Robot::Move::FORWARD_3,
        Robot::Move::BACKWARD_1,
        Robot::Move::TURN_LEFT,
        Robot::Move::TURN_RIGHT,
        Robot::Move::U_TURN
    };

    const std::vector<Robot::Status> statuses = {
        Robot::Status::NORTH,
        Robot::Status::SOUTH,
        Robot::Status::EAST,
        Robot::Status::WEST
    };

    for(const auto& [location, tile] : board.tiles) {
        for(auto status : statuses) {
            const Robot origin(location, status); // On teste les destinations à partir de l'origine pour chaque déplacement
            std::vector<Play> transitions;

            for(auto move : moves) { // Pour tous les coups
                Robot temp = origin;
                board.play(temp, move);

                if(temp.status != Robot::Status::DEAD)
                    transitions.emplace_back(temp, move);
            }

            graph.insert(std::make_pair(origin, transitions));
        }
    }
}