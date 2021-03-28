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

            mGraph.insert(std::make_pair(origin, transitions));
        }
    }
}

// Obligé d'utiliser une template et un foncteur pour la comparaison (le compilateur n'acceptais pas une lambda)
template<typename T, typename C>
struct comp {
    bool operator () (const std::pair<T, C>& lhs, const std::pair<T, C>& rhs) {return lhs.second > rhs.second; }
};

std::vector<Play> boardGraph::path(const Robot origin, const Robot destination) {
    // Variables de l'algorithme de Dijkstra :
    std::unordered_map<Robot, int, RobotHash, RobotEqual> d; // Distance
    std::unordered_map<Robot, Play, RobotHash, RobotEqual> p; // Predecesseur

    // Utilisation de paires (sommet + distance) pour éviter de créer un nouveau type)
    std::priority_queue<std::pair<Robot, int>, std::vector<std::pair<Robot, int>>, comp<Robot, int>> s; // File à priorité (basse)

    // Initialisation des distances à l'infini
    for(const auto& vertex : mGraph)
        d[vertex.first] = std::numeric_limits<int>::infinity();

    // On place l'origine dans la file avec une distance de 0
    s.push(std::make_pair(origin, 0));
    d[origin] = 0;

    // Traitment des sommets


}